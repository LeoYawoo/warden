#include "FDFile.h"
#include <fstream>
#include <sstream>

// CNullFrameDefStatus 实现
CNullFrameDefStatus::CNullFrameDefStatus() {
}

CNullFrameDefStatus::~CNullFrameDefStatus() {
}

// FDFile 实现
FDFile::FDFile()
    : m_status(FRAMEDEF_STATUS_OK)
    , m_rootNode(nullptr) {
}

FDFile::~FDFile() {
    Clear();
}

bool FDFile::LoadFromFile(const char* filePath) {
    std::ifstream file(filePath, std::ios::binary | std::ios::ate);
    if (!file.is_open()) {
        m_status = FRAMEDEF_STATUS_ERROR;
        m_errorMessage = "Failed to open file";
        return false;
    }

    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    std::vector<char> buffer(static_cast<size_t>(size));
    if (!file.read(buffer.data(), size)) {
        m_status = FRAMEDEF_STATUS_ERROR;
        m_errorMessage = "Failed to read file";
        return false;
    }

    return ParseXML(buffer.data());
}

bool FDFile::LoadFromMemory(const uint8_t* data, size_t size) {
    if (!data || size == 0) {
        m_status = FRAMEDEF_STATUS_ERROR;
        m_errorMessage = "Invalid data";
        return false;
    }

    return ParseXML(reinterpret_cast<const char*>(data));
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

    return ParseXML(reinterpret_cast<const char*>(data));
}

bool FDFile::ParseXML(const char* xmlContent) {
    if (!xmlContent) {
        m_status = FRAMEDEF_STATUS_ERROR;
        m_errorMessage = "Invalid XML content";
        return false;
    }

    // 清理旧数据
    Clear();

    // 查找根节点
    size_t pos = 0;
    m_rootNode = ParseXMLNode(xmlContent, pos);

    if (m_rootNode) {
        m_status = FRAMEDEF_STATUS_OK;
        return true;
    } else {
        m_status = FRAMEDEF_STATUS_ERROR;
        m_errorMessage = "Failed to parse XML";
        return false;
    }
}

FrameDefNode* FDFile::ParseXMLNode(const char* xmlContent, size_t& pos) {
    // 简化的 XML 解析实现
    // 实际实现需要更复杂的解析逻辑

    FrameDefNode* node = new FrameDefNode();
    node->type = NODE_TYPE_ELEMENT;

    // 跳过空白字符
    while (xmlContent[pos] == ' ' || xmlContent[pos] == '\t' ||
           xmlContent[pos] == '\n' || xmlContent[pos] == '\r') {
        pos++;
    }

    // 检查是否是开始标签
    if (xmlContent[pos] != '<') {
        delete node;
        return nullptr;
    }
    pos++; // 跳过 '<'

    // 读取节点名称
    size_t nameStart = pos;
    while (xmlContent[pos] != ' ' && xmlContent[pos] != '>' &&
           xmlContent[pos] != '/' && xmlContent[pos] != '\0') {
        pos++;
    }
    node->name = std::string(xmlContent + nameStart, pos - nameStart);

    // 解析属性
    ParseAttributes(xmlContent, pos, node);

    // 检查是否是自闭合标签
    if (xmlContent[pos] == '/') {
        pos++; // 跳过 '/'
        pos++; // 跳过 '>'
        return node;
    }

    // 跳过 '>'
    pos++;

    // 解析子节点
    while (xmlContent[pos] != '\0') {
        // 跳过空白字符
        while (xmlContent[pos] == ' ' || xmlContent[pos] == '\t' ||
               xmlContent[pos] == '\n' || xmlContent[pos] == '\r') {
            pos++;
        }

        // 检查是否是结束标签
        if (xmlContent[pos] == '<' && xmlContent[pos + 1] == '/') {
            // 跳过结束标签
            while (xmlContent[pos] != '>' && xmlContent[pos] != '\0') {
                pos++;
            }
            pos++; // 跳过 '>'
            return node;
        }

        // 解析子节点
        FrameDefNode* child = ParseXMLNode(xmlContent, pos);
        if (child) {
            node->children.push_back(child);
        } else {
            break;
        }
    }

    return node;
}

void FDFile::ParseAttributes(const char* xmlContent, size_t& pos, FrameDefNode* node) {
    while (xmlContent[pos] != '>' && xmlContent[pos] != '/' && xmlContent[pos] != '\0') {
        // 跳过空白字符
        while (xmlContent[pos] == ' ' || xmlContent[pos] == '\t') {
            pos++;
        }

        // 读取属性名
        size_t nameStart = pos;
        while (xmlContent[pos] != '=' && xmlContent[pos] != ' ' &&
               xmlContent[pos] != '>' && xmlContent[pos] != '\0') {
            pos++;
        }
        std::string attrName(xmlContent + nameStart, pos - nameStart);

        // 跳过 '='
        if (xmlContent[pos] == '=') {
            pos++;
        }

        // 读取属性值
        if (xmlContent[pos] == '"') {
            pos++; // 跳过开始引号
            size_t valueStart = pos;
            while (xmlContent[pos] != '"' && xmlContent[pos] != '\0') {
                pos++;
            }
            std::string attrValue(xmlContent + valueStart, pos - valueStart);
            pos++; // 跳过结束引号

            FrameDefAttribute attr;
            attr.name = attrName;
            attr.value = attrValue;
            node->attributes.push_back(attr);
        } else if (xmlContent[pos] == '\'') {
            pos++; // 跳过开始引号
            size_t valueStart = pos;
            while (xmlContent[pos] != '\'' && xmlContent[pos] != '\0') {
                pos++;
            }
            std::string attrValue(xmlContent + valueStart, pos - valueStart);
            pos++; // 跳过结束引号

            FrameDefAttribute attr;
            attr.name = attrName;
            attr.value = attrValue;
            node->attributes.push_back(attr);
        }
    }
}

const FrameDefNode* FDFile::FindNode(const char* name) const {
    if (!m_rootNode || !name) {
        return nullptr;
    }
    return FindNodeRecursive(m_rootNode, name);
}

FrameDefNode* FDFile::FindNodeRecursive(const FrameDefNode* node, const char* name) const {
    if (!node) {
        return nullptr;
    }

    if (node->name == name) {
        return const_cast<FrameDefNode*>(node);
    }

    for (const FrameDefNode* child : node->children) {
        FrameDefNode* found = FindNodeRecursive(child, name);
        if (found) {
            return found;
        }
    }

    return nullptr;
}

bool FDFile::GetNodeAttribute(const FrameDefNode* node, const char* attrName, std::string& value) const {
    if (!node || !attrName) {
        return false;
    }

    for (const FrameDefAttribute& attr : node->attributes) {
        if (attr.name == attrName) {
            value = attr.value;
            return true;
        }
    }

    return false;
}

size_t FDFile::GetChildCount(const FrameDefNode* node) const {
    if (!node) {
        return 0;
    }
    return node->children.size();
}

const FrameDefNode* FDFile::GetChild(const FrameDefNode* node, size_t index) const {
    if (!node || index >= node->children.size()) {
        return nullptr;
    }
    return node->children[index];
}

void FDFile::Clear() {
    if (m_rootNode) {
        FreeNode(m_rootNode);
        m_rootNode = nullptr;
    }
    m_status = FRAMEDEF_STATUS_OK;
    m_errorMessage.clear();
}

void FDFile::FreeNode(FrameDefNode* node) {
    if (!node) {
        return;
    }

    for (FrameDefNode* child : node->children) {
        FreeNode(child);
    }

    delete node;
}
