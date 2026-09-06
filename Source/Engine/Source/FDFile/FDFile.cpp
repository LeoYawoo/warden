#include "FDFile.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cstring>
#include <filesystem>

// ============================================================
// CNullFrameDefStatus 实现
// ============================================================
CNullFrameDefStatus::CNullFrameDefStatus() {
}

CNullFrameDefStatus::~CNullFrameDefStatus() {
}

// ============================================================
// FdfScanner 实现 - FDF 词法分析器
// ============================================================

FDFile::FdfScanner::FdfScanner(const char* content, size_t size)
    : pos(content)
    , end(content + size)
    , hasMore(true) {
}

void FDFile::FdfScanner::SkipWhitespace() {
    while (pos < end && (*pos == ' ' || *pos == '\t' || *pos == '\r' || *pos == '\n')) {
        pos++;
    }
}

void FDFile::FdfScanner::SkipComment() {
    if (pos + 1 < end) {
        if (pos[0] == '/' && pos[1] == '/') {
            // 单行注释
            while (pos < end && *pos != '\n') {
                pos++;
            }
            pos++; // 跳过换行符
        } else if (pos[0] == '/' && pos[1] == '*') {
            // 多行注释
            pos += 2;
            while (pos + 1 < end && !(pos[0] == '*' && pos[1] == '/')) {
                pos++;
            }
            if (pos + 1 < end) {
                pos += 2; // 跳过 */
            }
        }
    }
}

std::string FDFile::FdfScanner::NextToken() {
    SkipWhitespace();
    SkipComment();
    SkipWhitespace();

    if (pos >= end) {
        hasMore = false;
        return "";
    }

    char c = *pos;

    // 大括号
    if (c == '{' || c == '}' || c == ',') {
        currentToken = std::string(1, c);
        pos++;
        return currentToken;
    }

    // 字符串字面量
    if (c == '"') {
        pos++; // 跳过开始引号
        size_t start = 0;
        std::string result;
        while (pos < end && *pos != '"') {
            if (*pos == '\\' && pos + 1 < end) {
                pos++;
                switch (*pos) {
                    case 'n': result += '\n'; break;
                    case 't': result += '\t'; break;
                    case '\\': result += '\\'; break;
                    case '"': result += '"'; break;
                    default: result += *pos; break;
                }
            } else {
                result += *pos;
            }
            pos++;
        }
        if (pos < end) {
            pos++; // 跳过结束引号
        }
        return result;
    }

    // 数字或标识符
    const char* startPos = pos;

    while (pos < end && *pos != ' ' && *pos != '\t' && *pos != '\r' &&
           *pos != '\n' && *pos != '{' && *pos != '}' && *pos != ',' && *pos != '"') {
        pos++;
    }

    return std::string(startPos, pos - startPos);
}

std::string FDFile::FdfScanner::PeekToken() {
    // 保存状态
    const char* savedPos = pos;
    bool savedHasMore = hasMore;

    std::string token = NextToken();

    // 恢复状态
    pos = savedPos;
    hasMore = savedHasMore;

    return token;
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

    // 读取 TOC 文件
    std::ifstream tocFile(tocPath, std::ios::binary);
    if (!tocFile.is_open()) {
        m_status = FRAMEDEF_STATUS_ERROR;
        m_errorMessage = "Failed to open TOC file: " + std::string(tocPath);
        return false;
    }

    // 获取基础路径
    std::filesystem::path path(tocPath);
    m_basePath = path.parent_path().string();

    // 读取 TOC 内容
    std::ostringstream ss;
    ss << tocFile.rdbuf();
    std::string tocContent = ss.str();

    // 解析 TOC 文件 (每行一个文件路径)
    std::istringstream stream(tocContent);
    std::string line;
    bool anySuccess = false;

    while (std::getline(stream, line)) {
        // 跳过空行和注释
        if (line.empty() || line[0] == '/' || line[0] == '#') {
            continue;
        }

        // 去除行尾 \r
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }

        if (line.empty()) {
            continue;
        }

        // 构建完整路径
        std::string fullPath = m_basePath + "/" + line;

        // 加载 FDF 文件
        if (LoadFDFFile(fullPath.c_str())) {
            anySuccess = true;
        }
    }

    m_status = anySuccess ? FRAMEDEF_STATUS_OK : FRAMEDEF_STATUS_ERROR;
    return anySuccess;
}

bool FDFile::LoadFDFFile(const char* filePath) {
    if (!filePath) {
        return false;
    }

    // 检查是否已包含 (防止循环包含)
    for (const auto& included : m_includedFiles) {
        if (included == filePath) {
            return true; // 已包含，跳过
        }
    }

    std::ifstream file(filePath, std::ios::binary);
    if (!file.is_open()) {
        return false;
    }

    // 读取文件内容
    std::ostringstream ss;
    ss << file.rdbuf();
    std::string content = ss.str();

    // 记录已包含
    m_includedFiles.push_back(filePath);

    // 解析 FDF 内容
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

bool FDFile::ParseFDFContent(const char* content, size_t size) {
    if (!content || size == 0) {
        m_status = FRAMEDEF_STATUS_ERROR;
        m_errorMessage = "Invalid FDF content";
        return false;
    }

    FdfScanner scanner(content, size);

    // 解析所有顶层语句
    while (scanner.HasMore()) {
        std::string token = scanner.PeekToken();
        if (token.empty()) {
            break;
        }

        if (!ParseTopLevel(scanner)) {
            // 解析错误，但继续尝试
            // 跳过到下一个语句
            while (scanner.HasMore() && scanner.PeekToken() != "Frame" &&
                   scanner.PeekToken() != "StringList" && scanner.PeekToken() != "IncludeFile") {
                scanner.NextToken();
            }
        }
    }

    m_status = FRAMEDEF_STATUS_OK;
    return true;
}

bool FDFile::ParseTopLevel(FdfScanner& scanner) {
    std::string token = scanner.NextToken();

    if (token == "Frame") {
        FdfNode* frame = ParseFrame(scanner);
        if (frame) {
            if (!m_rootNode) {
                m_rootNode = frame;
            }
            // 注册到帧表
            if (!frame->name.empty()) {
                m_frames[frame->name] = frame;
            }
            return true;
        }
        return false;
    }
    else if (token == "StringList") {
        return ParseStringList(scanner);
    }
    else if (token == "IncludeFile") {
        std::string path = ReadStringLiteral(scanner);
        if (!path.empty()) {
            // 构建完整路径
            std::string fullPath = m_basePath + "/" + path;
            return ParseIncludeFile(scanner, fullPath);
        }
        return false;
    }

    return false;
}

FdfNode* FDFile::ParseFrame(FdfScanner& scanner) {
    FdfNode* frame = new FdfNode();
    frame->type = FDF_NODE_FRAME;

    // 读取帧类型: "FRAME", "TEXT", "SPRITE", etc.
    frame->frameType = ReadStringLiteral(scanner);

    // 读取帧名称
    frame->name = ReadStringLiteral(scanner);

    // 检查 INHERITS
    std::string token = scanner.PeekToken();
    if (token == "INHERITS") {
        scanner.NextToken(); // 消费 INHERITS

        // 检查是否是 WITHCHILDREN
        token = scanner.PeekToken();
        if (token == "WITHCHILDREN") {
            scanner.NextToken();
            frame->withChildren = true;
        }

        // 读取继承的模板名
        frame->inheritsFrom = ReadStringLiteral(scanner);
    }

    // 读取左大括号
    token = scanner.NextToken();
    if (token != "{") {
        delete frame;
        return nullptr;
    }

    // 解析 Frame 内部内容
    ParseFrameBody(scanner, frame);

    // 读取右大括号
    token = scanner.NextToken();
    if (token != "}") {
        // 错误恢复
    }

    return frame;
}

bool FDFile::ParseStringList(FdfScanner& scanner) {
    // 读取左大括号
    std::string token = scanner.NextToken();
    if (token != "{") {
        return false;
    }

    // 解析字符串条目
    while (scanner.HasMore()) {
        token = scanner.PeekToken();
        if (token == "}") {
            scanner.NextToken(); // 消费 }
            break;
        }

        // 读取键名
        std::string key = scanner.NextToken();
        if (key.empty()) {
            break;
        }

        // 读取字符串值
        std::string value = ReadStringLiteral(scanner);

        // 存储字符串
        m_strings[key] = value;

        // 跳过逗号 (如果有)
        token = scanner.PeekToken();
        if (token == ",") {
            scanner.NextToken();
        }
    }

    return true;
}

bool FDFile::ParseIncludeFile(FdfScanner& scanner, const std::string& path) {
    // 检查是否已包含
    for (const auto& included : m_includedFiles) {
        if (included == path) {
            return true; // 防止循环包含
        }
    }

    // 读取文件并解析
    std::ifstream file(path, std::ios::binary);
    if (!file.is_open()) {
        return false;
    }

    std::ostringstream ss;
    ss << file.rdbuf();
    std::string content = ss.str();

    // 记录已包含
    m_includedFiles.push_back(path);

    // 解析内容
    FdfScanner includedScanner(content.c_str(), content.size());
    while (includedScanner.HasMore()) {
        std::string token = includedScanner.PeekToken();
        if (token.empty()) {
            break;
        }
        ParseTopLevel(includedScanner);
    }

    return true;
}

void FDFile::ParseFrameBody(FdfScanner& scanner, FdfNode* frame) {
    while (scanner.HasMore()) {
        std::string token = scanner.PeekToken();
        if (token.empty() || token == "}") {
            break;
        }

        // 检查是否是子 Frame
        if (token == "Frame") {
            scanner.NextToken(); // 消费 Frame
            FdfNode* child = ParseFrame(scanner);
            if (child) {
                frame->children.push_back(child);
            }
        }
        // 检查是否是 Texture 子节点 (简写形式)
        else if (token == "Texture") {
            scanner.NextToken(); // 消费 Texture
            FdfNode* texture = new FdfNode();
            texture->type = FDF_NODE_FRAME;
            texture->frameType = "TEXTURE";

            // 读取左大括号
            token = scanner.NextToken();
            if (token == "{") {
                // 解析 Texture 属性
                while (scanner.HasMore()) {
                    token = scanner.PeekToken();
                    if (token == "}") {
                        scanner.NextToken();
                        break;
                    }
                    FdfAttribute attr = ParseAttribute(scanner);
                    texture->attributes.push_back(attr);
                }
            }

            frame->children.push_back(texture);
        }
        // 检查其他关键字
        else if (token == "IncludeFile") {
            scanner.NextToken(); // 消费 IncludeFile
            std::string path = ReadStringLiteral(scanner);
            if (!path.empty()) {
                std::string fullPath = m_basePath + "/" + path;
                ParseIncludeFile(scanner, fullPath);
            }
        }
        else {
            // 普通属性
            FdfAttribute attr = ParseAttribute(scanner);
            frame->attributes.push_back(attr);
        }
    }
}

FdfAttribute FDFile::ParseAttribute(FdfScanner& scanner) {
    FdfAttribute attr;

    // 读取属性名
    attr.name = scanner.NextToken();

    // 读取属性值
    std::string token = scanner.PeekToken();

    // 检查是否是字符串字面量
    if (!token.empty() && token[0] == '"') {
        attr.value = ReadStringLiteral(scanner);
    }
    // 检查是否是数字
    else if (!token.empty() && (isdigit(token[0]) || token[0] == '-' || token[0] == '.')) {
        attr.value = scanner.NextToken();

        // 检查是否是多参数属性 (如 SetPoint TOPLEFT, "Parent", TOPLEFT, 0.1, 0.2)
        token = scanner.PeekToken();
        while (!token.empty() && token != "," && token != "}" &&
               token != "Frame" && token != "Texture" && token != "IncludeFile" &&
               token != "StringList") {
            attr.args.push_back(scanner.NextToken());
            token = scanner.PeekToken();
        }
    }
    // 检查是否是关键字 (如 SetAllPoints, DecorateFileNames)
    else if (!token.empty() && token != "," && token != "}" &&
             token != "Frame" && token != "Texture" && token != "IncludeFile" &&
             token != "StringList") {
        attr.value = scanner.NextToken();

        // 继续读取参数
        token = scanner.PeekToken();
        while (!token.empty() && token != "," && token != "}" &&
               token != "Frame" && token != "Texture" && token != "IncludeFile" &&
               token != "StringList") {
            attr.args.push_back(scanner.NextToken());
            token = scanner.PeekToken();
        }
    }

    // 跳过逗号
    token = scanner.PeekToken();
    if (token == ",") {
        scanner.NextToken();
    }

    return attr;
}

std::string FDFile::ReadStringLiteral(FdfScanner& scanner) {
    std::string token = scanner.NextToken();

    // 如果已经是字符串内容 (不含引号)，直接返回
    // Scanner 已经处理了引号
    return token;
}

bool FDFile::MatchToken(FdfScanner& scanner, const std::string& expected) {
    std::string token = scanner.NextToken();
    return token == expected;
}

// ============================================================
// 查询接口
// ============================================================

const FdfNode* FDFile::FindFrame(const char* name) const {
    if (!name) {
        return nullptr;
    }

    auto it = m_frames.find(name);
    if (it != m_frames.end()) {
        return it->second;
    }

    return nullptr;
}

bool FDFile::GetString(const char* key, std::string& value) const {
    if (!key) {
        return false;
    }

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
    if (!node) {
        return;
    }

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
    // 旧接口兼容 - 实际调用 FDF 解析
    if (!xmlContent) {
        m_status = FRAMEDEF_STATUS_ERROR;
        m_errorMessage = "Invalid content";
        return false;
    }

    return ParseFDFContent(xmlContent, strlen(xmlContent));
}
