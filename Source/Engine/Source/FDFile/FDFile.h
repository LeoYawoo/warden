#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include <unordered_map>
#include "../Base/CDataStore.h"

// FDFile - UI 框架定义文件解析器
// 基于 IDA 反编译分析实现
// FDF 格式: 自定义 Blizzard UI 定义语言 (非 XML)

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

// FDF 帧类型 (IDA: FRAME, SPRITE, BACKDROP, LISTBOX, DIALOG, EDITBOX, CHECKBOX)
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

// FDF 属性 (如 Width 0.1, File "path.blp")
struct FdfAttribute {
    std::string name;
    std::string value;
    std::vector<std::string> args;  // 多参数: SetPoint TOPLEFT, "Parent", TOPLEFT, 0.1, 0.2
};

// FDF 节点 (帧定义或属性块)
struct FdfNode {
    FDF_NODE_TYPE type;
    std::string name;           // 节点名称 (帧名称或属性名)
    std::string frameType;      // 帧类型 ("FRAME", "TEXT", etc.)
    std::string inheritsFrom;   // INHERITS 继承的模板名
    std::string value;          // 属性值
    std::vector<FdfAttribute> attributes;
    std::vector<FdfNode*> children;
    bool withChildren;          // INHERITS WITHCHILDREN 标志
};

// StringList 条目
struct StringEntry {
    std::string key;
    std::string value;
};

// DEFFILENAMENODE - IDA 反编译中的文件名节点
struct DefFileNameNode {
    char name[260];  // MAX_PATH
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
// BASEFRAMEHASHNODE - IDA 反编译中的帧哈希节点
// ============================================================
struct BASEFRAMEHASHNODE {
    // 链表指针 (TSLink)
    BASEFRAMEHASHNODE* next;
    BASEFRAMEHASHNODE* prev;

    // 帧信息
    int32_t nodeId;
    char name[260];         // 帧名称
    FdfNode* frameDef;      // 帧定义节点
    bool isValid;
    bool isInUse;           // IDA offset 48 检查
};

// ============================================================
// STRINGHASHNODE - IDA 反编译中的字符串哈希节点
// ============================================================
struct STRINGHASHNODE {
    // 链表指针
    STRINGHASHNODE* next;
    STRINGHASHNODE* prev;

    // 字符串信息
    int32_t nodeId;
    char key[260];          // 字符串键
    char value[1024];       // 字符串值
    bool isInUse;           // IDA offset 24 检查
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
    // FDF 词法分析
    struct FdfScanner {
        const char* pos;
        const char* end;
        std::string currentToken;
        bool hasMore;

        FdfScanner(const char* content, size_t size);
        std::string NextToken();
        std::string PeekToken();
        void SkipWhitespace();
        void SkipComment();
        bool HasMore() const { return hasMore; }
    };

    // 解析 FDF 内容
    bool ParseFDFContent(const char* content, size_t size);

    // 解析顶层语句
    bool ParseTopLevel(FdfScanner& scanner);

    // 解析 Frame 定义
    FdfNode* ParseFrame(FdfScanner& scanner);

    // 解析 StringList
    bool ParseStringList(FdfScanner& scanner);

    // 解析 IncludeFile
    bool ParseIncludeFile(FdfScanner& scanner, const std::string& path);

    // 解析属性列表 (Frame 内部)
    void ParseFrameBody(FdfScanner& scanner, FdfNode* frame);

    // 解析单个属性
    FdfAttribute ParseAttribute(FdfScanner& scanner);

    // 匹配 token
    bool MatchToken(FdfScanner& scanner, const std::string& expected);

    // 读取字符串字面量
    std::string ReadStringLiteral(FdfScanner& scanner);

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

    // 全局帧哈希表 (IDA: dword_F6B418)
    // BASEFRAMEHASHNODE* m_frameHash;

    // 全局字符串哈希表
    // STRINGHASHNODE* m_stringHash;
};
