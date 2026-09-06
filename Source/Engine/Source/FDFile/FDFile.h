#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include <unordered_map>
#include "../Base/CDataStore.h"

// Forward declarations
class CStatus;

// FDFile - UI 框架定义文件解析器
// 基于 IDA 反编译分析实现
// FDF 格式: 自定义 Blizzard UI 定义语言 (非 XML)
//
// IDA 架构:
// CFdScanner → HANDLERHASH → 调用处理函数

// ============================================================
// 枚举定义
// ============================================================

// 框架定义状态
enum FRAMEDEF_STATUS {
    FRAMEDEF_STATUS_OK = 0,
    FRAMEDEF_STATUS_ERROR = 1,
    FRAMEDEF_STATUS_NOT_FOUND = 2,
};

// FDF 节点类型
enum FDF_NODE_TYPE {
    FDF_NODE_FRAME = 0,      // Frame "TYPE" "NAME" { ... }
    FDF_NODE_STRING_LIST,    // StringList { ... }
    FDF_NODE_INCLUDE,        // IncludeFile "path"
    FDF_NODE_PROPERTY,       // 属性: Width 0.1, Height 0.2
    FDF_NODE_COMMENT,        // 注释: // 或 /* */
};

// FDF 帧类型
enum FDF_FRAME_TYPE {
    FDF_FRAME_UNKNOWN = 0,
    FDF_FRAME_FRAME,         // "FRAME"
    FDF_FRAME_SPRITE,        // "SPRITE"
    FDF_FRAME_BACKDROP,      // "BACKDROP"
    FDF_FRAME_LISTBOX,       // "LISTBOX"
    FDF_FRAME_DIALOG,        // "DIALOG"
    FDF_FRAME_EDITBOX,       // "EDITBOX"
    FDF_FRAME_CHECKBOX,      // "CHECKBOX"
    FDF_FRAME_SIMPLEFRAME,   // "SIMPLEFRAME"
    FDF_FRAME_GLUETEXTBUTTON, // "GLUETEXTBUTTON"
    FDF_FRAME_GLUEBUTTON,    // "GLUEBUTTON"
    FDF_FRAME_TEXT,          // "TEXT"
    FDF_FRAME_TEXTURE,       // "Texture" (子节点)
};

// ============================================================
// 数据结构
// ============================================================

// FDF 属性
struct FdfAttribute {
    std::string name;
    std::string value;
    std::vector<std::string> args;
};

// FDF 节点
struct FdfNode {
    FDF_NODE_TYPE type;
    std::string name;
    std::string frameType;
    std::string inheritsFrom;
    std::string value;
    std::vector<FdfAttribute> attributes;
    std::vector<FdfNode*> children;
    bool withChildren;
};

// StringList 条目
struct StringEntry {
    std::string key;
    std::string value;
};

// ============================================================
// CFdScanner - FDF 词法分析器
// IDA 中的类 (10CFdScanner)
// ============================================================
class CFdScanner {
public:
    CFdScanner(CStatus* status, const char* content, int size);
    ~CFdScanner();

    // 读取下一个 token
    std::string NextToken();

    // 查看下一个 token (不消费)
    std::string PeekToken();

    // 跳过空白字符
    void SkipWhitespace();

    // 跳过注释
    void SkipComment();

    // 读取字符串字面量
    std::string ReadStringLiteral();

    // 是否还有更多 token
    bool HasMore() const;

    // 获取状态
    CStatus* GetStatus() const { return m_status; }

private:
    CStatus* m_status;
    const char* m_pos;
    const char* m_end;
    bool m_hasMore;
};

// ============================================================
// CNullFrameDefStatus
// ============================================================
class CNullFrameDefStatus {
public:
    CNullFrameDefStatus();
    ~CNullFrameDefStatus();
};

// ============================================================
// FDFile - FDF 文件解析器
// ============================================================
class FDFile {
public:
    FDFile();
    ~FDFile();

    // 加载 FrameDef.toc 文件 (入口点)
    bool LoadFrameDef(const char* tocPath);

    // 加载单个 FDF 文件
    bool LoadFDFFile(const char* filePath);

    // 从内存加载 FDF 内容
    bool LoadFromMemory(const char* content, size_t size);

    // 从数据存储加载
    bool LoadFromDataStore(CDataStore& dataStore);

    // 获取解析状态
    FRAMEDEF_STATUS GetStatus() const { return m_status; }

    // 获取错误消息
    const char* GetErrorMessage() const { return m_errorMessage.c_str(); }

    // 获取根节点
    const FdfNode* GetRootNode() const { return m_rootNode; }

    // 查找帧节点
    const FdfNode* FindFrame(const char* name) const;

    // 获取字符串值
    bool GetString(const char* key, std::string& value) const;

    // 获取所有字符串
    const std::unordered_map<std::string, std::string>& GetStrings() const { return m_strings; }

    // 获取所有帧定义
    const std::unordered_map<std::string, FdfNode*>& GetFrames() const { return m_frames; }

    // 清理资源
    void Clear();

    // 检查是否有效
    bool IsValid() const { return m_rootNode != nullptr; }

    // 兼容旧接口
    bool ParseXML(const char* xmlContent);

private:
    // IDA 架构: 核心解析循环 (sub_1F5440)
    bool ParseFDFContent(const char* content, size_t size);

    // 递归释放节点
    void FreeNode(FdfNode* node);

    // 帧类型字符串转枚举
    FDF_FRAME_TYPE GetFrameType(const std::string& typeStr) const;

    // 全局变量
    FRAMEDEF_STATUS m_status;
    std::string m_errorMessage;
    FdfNode* m_rootNode;
    std::string m_basePath;

    // 字符串表 (StringList)
    std::unordered_map<std::string, std::string> m_strings;

    // 帧定义表 (按名称索引)
    std::unordered_map<std::string, FdfNode*> m_frames;

    // 已包含的文件 (防止循环包含)
    std::vector<std::string> m_includedFiles;
};
