#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include "../Base/CDataStore.h"

// FDFile - UI 框架定义文件解析器
// 基于 IDA 反编译分析实现

// 框架定义状态
enum FRAMEDEF_STATUS {
    FRAMEDEF_STATUS_OK = 0,
    FRAMEDEF_STATUS_ERROR = 1,
    FRAMEDEF_STATUS_NOT_FOUND = 2,
};

// 框架定义节点类型
enum FRAMEDEF_NODE_TYPE {
    NODE_TYPE_ELEMENT = 0,
    NODE_TYPE_ATTRIBUTE = 1,
    NODE_TYPE_TEXT = 2,
};

// 框架定义属性
struct FrameDefAttribute {
    std::string name;
    std::string value;
};

// 框架定义节点
struct FrameDefNode {
    FRAMEDEF_NODE_TYPE type;
    std::string name;
    std::string value;
    std::vector<FrameDefAttribute> attributes;
    std::vector<FrameDefNode*> children;
};

// CNullFrameDefStatus - 空框架定义状态
class CNullFrameDefStatus {
public:
    CNullFrameDefStatus();
    ~CNullFrameDefStatus();
};

// FDFile - UI 框架定义文件解析器
class FDFile {
public:
    // 构造函数
    FDFile();
    ~FDFile();

    // 加载框架定义文件
    bool LoadFromFile(const char* filePath);

    // 从内存加载
    bool LoadFromMemory(const uint8_t* data, size_t size);

    // 从数据存储加载
    bool LoadFromDataStore(CDataStore& dataStore);

    // 解析 XML 格式
    bool ParseXML(const char* xmlContent);

    // 获取解析状态
    FRAMEDEF_STATUS GetStatus() const { return m_status; }

    // 获取错误消息
    const char* GetErrorMessage() const { return m_errorMessage.c_str(); }

    // 获取根节点
    const FrameDefNode* GetRootNode() const { return m_rootNode; }

    // 查找节点
    const FrameDefNode* FindNode(const char* name) const;

    // 获取节点属性
    bool GetNodeAttribute(const FrameDefNode* node, const char* attrName, std::string& value) const;

    // 获取子节点数量
    size_t GetChildCount(const FrameDefNode* node) const;

    // 获取子节点
    const FrameDefNode* GetChild(const FrameDefNode* node, size_t index) const;

    // 清理资源
    void Clear();

    // 检查是否有效
    bool IsValid() const { return m_rootNode != nullptr; }

private:
    // 解析 XML 节点
    FrameDefNode* ParseXMLNode(const char* xmlContent, size_t& pos);

    // 解析属性
    void ParseAttributes(const char* xmlContent, size_t& pos, FrameDefNode* node);

    // 查找节点
    FrameDefNode* FindNodeRecursive(const FrameDefNode* node, const char* name) const;

    // 释放节点内存
    void FreeNode(FrameDefNode* node);

    FRAMEDEF_STATUS m_status;
    std::string m_errorMessage;
    FrameDefNode* m_rootNode;
};
