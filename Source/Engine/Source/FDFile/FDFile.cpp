#include "FDFile.h"
#include "Handlers/HandlerHash.h"
#include "Handlers/FrameHandlers.h"
#include "../Agile/CStatus.h"
#include <fstream>
#include <sstream>
#include <cstring>
#include <filesystem>

// FDFile.cpp - FDF 文件解析器实现
// 基于 IDA 反编译分析实现
//
// IDA 架构流程:
// 1. LoadFrameDef (sub_1F5B56) - 加载 TOC 文件
// 2. LoadFDFFile (sub_1F59A6) - 加载单个 FDF 文件
// 3. ParseFDFContent (sub_1F5440) - 核心解析循环
//    - 创建 CFdScanner
//    - 循环: 读取 token → 查找处理器 → 调用处理器
// 4. RegisterHandlers (sub_1F571E) - 注册处理器
// 5. InitializeDefaultHandlers (sub_1F5634) - 初始化默认处理器

// ============================================================
// CNullFrameDefStatus 实现
// ============================================================
CNullFrameDefStatus::CNullFrameDefStatus() {
}

CNullFrameDefStatus::~CNullFrameDefStatus() {
}

// ============================================================
// CFdScanner 实现 - IDA: 10CFdScanner
// ============================================================

CFdScanner::CFdScanner(CStatus* status, const char* content, int size)
    : m_status(status)
    , m_pos(content)
    , m_end(content + size)
    , m_hasMore(true) {
}

CFdScanner::~CFdScanner() {
}

void CFdScanner::SkipWhitespace() {
    while (m_pos < m_end && (*m_pos == ' ' || *m_pos == '\t' || *m_pos == '\r' || *m_pos == '\n')) {
        m_pos++;
    }
}

void CFdScanner::SkipComment() {
    if (m_pos + 1 < m_end) {
        if (m_pos[0] == '/' && m_pos[1] == '/') {
            // 单行注释
            while (m_pos < m_end && *m_pos != '\n') {
                m_pos++;
            }
            m_pos++;
        } else if (m_pos[0] == '/' && m_pos[1] == '*') {
            // 多行注释
            m_pos += 2;
            while (m_pos + 1 < m_end && !(m_pos[0] == '*' && m_pos[1] == '/')) {
                m_pos++;
            }
            if (m_pos + 1 < m_end) {
                m_pos += 2;
            }
        }
    }
}

std::string CFdScanner::NextToken() {
    SkipWhitespace();
    SkipComment();
    SkipWhitespace();

    if (m_pos >= m_end) {
        m_hasMore = false;
        return "";
    }

    char c = *m_pos;

    // 大括号和逗号
    if (c == '{' || c == '}' || c == ',') {
        std::string token(1, c);
        m_pos++;
        return token;
    }

    // 字符串字面量
    if (c == '"') {
        return ReadStringLiteral();
    }

    // 标识符或数字
    const char* startPos = m_pos;
    while (m_pos < m_end && *m_pos != ' ' && *m_pos != '\t' && *m_pos != '\r' &&
           *m_pos != '\n' && *m_pos != '{' && *m_pos != '}' && *m_pos != ',' && *m_pos != '"') {
        m_pos++;
    }

    return std::string(startPos, m_pos - startPos);
}

std::string CFdScanner::PeekToken() {
    const char* savedPos = m_pos;
    bool savedHasMore = m_hasMore;

    std::string token = NextToken();

    m_pos = savedPos;
    m_hasMore = savedHasMore;

    return token;
}

std::string CFdScanner::ReadStringLiteral() {
    if (m_pos >= m_end || *m_pos != '"') {
        return "";
    }

    m_pos++; // 跳过开始引号
    std::string result;
    while (m_pos < m_end && *m_pos != '"') {
        if (*m_pos == '\\' && m_pos + 1 < m_end) {
            m_pos++;
            switch (*m_pos) {
                case 'n': result += '\n'; break;
                case 't': result += '\t'; break;
                case '\\': result += '\\'; break;
                case '"': result += '"'; break;
                default: result += *m_pos; break;
            }
        } else {
            result += *m_pos;
        }
        m_pos++;
    }
    if (m_pos < m_end) {
        m_pos++; // 跳过结束引号
    }
    return result;
}

bool CFdScanner::HasMore() const {
    return m_hasMore && m_pos < m_end;
}

// ============================================================
// FDFile 实现
// ============================================================

FDFile::FDFile()
    : m_status(FRAMEDEF_STATUS_OK)
    , m_rootNode(nullptr) {
}

FDFile::~FDFile() {
    Clear();
}

bool FDFile::LoadFrameDef(const char* tocPath) {
    if (!tocPath) {
        m_status = FRAMEDEF_STATUS_ERROR;
        m_errorMessage = "Invalid TOC path";
        return false;
    }

    std::ifstream tocFile(tocPath, std::ios::binary);
    if (!tocFile.is_open()) {
        m_status = FRAMEDEF_STATUS_ERROR;
        m_errorMessage = "Failed to open TOC file: " + std::string(tocPath);
        return false;
    }

    std::filesystem::path path(tocPath);
    m_basePath = path.parent_path().string();

    std::ostringstream ss;
    ss << tocFile.rdbuf();
    std::string tocContent = ss.str();

    std::istringstream stream(tocContent);
    std::string line;
    bool anySuccess = false;

    while (std::getline(stream, line)) {
        if (line.empty() || line[0] == '/' || line[0] == '#') {
            continue;
        }
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }
        if (line.empty()) continue;

        std::string fullPath = m_basePath + "/" + line;
        if (LoadFDFFile(fullPath.c_str())) {
            anySuccess = true;
        }
    }

    m_status = anySuccess ? FRAMEDEF_STATUS_OK : FRAMEDEF_STATUS_ERROR;
    return anySuccess;
}

bool FDFile::LoadFDFFile(const char* filePath) {
    if (!filePath) return false;

    for (const auto& included : m_includedFiles) {
        if (included == filePath) return true;
    }

    std::ifstream file(filePath, std::ios::binary);
    if (!file.is_open()) return false;

    std::ostringstream ss;
    ss << file.rdbuf();
    std::string content = ss.str();

    m_includedFiles.push_back(filePath);
    return ParseFDFContent(content.c_str(), content.size());
}

bool FDFile::LoadFromMemory(const char* content, size_t size) {
    if (!content || size == 0) {
        m_status = FRAMEDEF_STATUS_ERROR;
        m_errorMessage = "Invalid data";
        return false;
    }
    return ParseFDFContent(content, size);
}

bool FDFile::LoadFromDataStore(CDataStore& dataStore) {
    if (dataStore.Size() == 0) {
        m_status = FRAMEDEF_STATUS_ERROR;
        m_errorMessage = "Empty data store";
        return false;
    }

    const void* data = nullptr;
    uint32_t size = 0;
    uint32_t alloc = 0;
    dataStore.GetBufferParams(&data, &size, &alloc);

    if (!data || size == 0) {
        m_status = FRAMEDEF_STATUS_ERROR;
        m_errorMessage = "Invalid data store buffer";
        return false;
    }

    return ParseFDFContent(reinterpret_cast<const char*>(data), size);
}

// ============================================================
// 核心解析循环 - IDA: sub_1F5440
// 使用 HANDLERHASH 分发架构
// ============================================================
bool FDFile::ParseFDFContent(const char* content, size_t size) {
    if (!content || size == 0) {
        m_status = FRAMEDEF_STATUS_ERROR;
        m_errorMessage = "Invalid FDF content";
        return false;
    }

    // IDA: CFdScanner::CFdScanner(v13, a4, v14, 1024)
    CStatus status;
    CFdScanner scanner(&status, content, static_cast<int>(size));

    // IDA: sub_1F5634() - 初始化处理器
    FrameHandlers::InitializeDefaultHandlers();

    // IDA: sub_1F571E() - 注册处理器
    FrameHandlers::RegisterAllHandlers();

    // IDA 核心循环:
    // do {
    //     v10 = sub_5DF3D8(v13);  // 读取 token
    //     if (!v10) break;
    //     v8 = TSHashTable<HANDLERHASH>::Ptr(&dword_F33A00, v10);  // 查找处理器
    //     if (!v8) break;
    //     v9 = *(handler*)(v8 + 24);  // 获取处理函数
    //     if (!v9) break;
    // } while (v9(v13, a2, a3, a4));  // 调用处理函数

    HandlerHash& handlerHash = GlobalHandlers::GetHandlerHash();

    while (scanner.HasMore()) {
        std::string token = scanner.PeekToken();
        if (token.empty()) break;

        // 查找处理器
        FdfHandlerFunc handler = handlerHash.Find(token);
        if (!handler) {
            // 未知 token，跳过
            scanner.NextToken();
            continue;
        }

        // 调用处理器
        int result = handler(&scanner, 0, 0, &status);
        if (result == 0) {
            // 处理器返回 0，停止解析
            break;
        }
    }

    m_status = FRAMEDEF_STATUS_OK;
    return true;
}

// ============================================================
// 查询接口
// ============================================================

const FdfNode* FDFile::FindFrame(const char* name) const {
    if (!name) return nullptr;
    auto it = m_frames.find(name);
    if (it != m_frames.end()) return it->second;
    return nullptr;
}

bool FDFile::GetString(const char* key, std::string& value) const {
    if (!key) return false;
    auto it = m_strings.find(key);
    if (it != m_strings.end()) {
        value = it->second;
        return true;
    }
    return false;
}

void FDFile::Clear() {
    if (m_rootNode) {
        FreeNode(m_rootNode);
        m_rootNode = nullptr;
    }
    m_strings.clear();
    m_frames.clear();
    m_includedFiles.clear();
    m_status = FRAMEDEF_STATUS_OK;
    m_errorMessage.clear();
}

void FDFile::FreeNode(FdfNode* node) {
    if (!node) return;
    for (FdfNode* child : node->children) {
        FreeNode(child);
    }
    delete node;
}

FDF_FRAME_TYPE FDFile::GetFrameType(const std::string& typeStr) const {
    if (typeStr == "FRAME") return FDF_FRAME_FRAME;
    if (typeStr == "TEXT") return FDF_FRAME_TEXT;
    if (typeStr == "SPRITE") return FDF_FRAME_SPRITE;
    if (typeStr == "BACKDROP") return FDF_FRAME_BACKDROP;
    if (typeStr == "LISTBOX") return FDF_FRAME_LISTBOX;
    if (typeStr == "DIALOG") return FDF_FRAME_DIALOG;
    if (typeStr == "EDITBOX") return FDF_FRAME_EDITBOX;
    if (typeStr == "CHECKBOX") return FDF_FRAME_CHECKBOX;
    if (typeStr == "SIMPLEFRAME") return FDF_FRAME_SIMPLEFRAME;
    if (typeStr == "GLUETEXTBUTTON") return FDF_FRAME_GLUETEXTBUTTON;
    if (typeStr == "GLUEBUTTON") return FDF_FRAME_GLUEBUTTON;
    if (typeStr == "Texture") return FDF_FRAME_TEXTURE;
    return FDF_FRAME_UNKNOWN;
}

// ============================================================
// 兼容旧接口
// ============================================================

bool FDFile::ParseXML(const char* xmlContent) {
    if (!xmlContent) {
        m_status = FRAMEDEF_STATUS_ERROR;
        m_errorMessage = "Invalid content";
        return false;
    }
    return ParseFDFContent(xmlContent, strlen(xmlContent));
}
