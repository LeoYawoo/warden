#pragma once
// FrameHandlers.h - 帧处理器接口
// 基于 IDA 反编译分析实现
// 原始文件: Engine/Source/FDFile/Handlers/FrameHandlers.cpp

#include <cstdint>
#include <string>

// 前向声明
class CFdScanner;
class CStatus;
struct FdfNode;
struct FdfAttribute;

// ============================================================
// TYPEHANDLERSTRUCT - 帧类型处理器结构
// IDA 中的结构, 存储每种帧类型的处理函数
// ============================================================
struct TYPEHANDLERSTRUCT {
    uint32_t typeHash;          // 帧类型哈希值
    uint32_t reserved1;         // 保留
    uint32_t reserved2;         // 保留
    uint32_t reserved3;         // 保留
    uint32_t reserved4;         // 保留
    uint32_t reserved5;         // 保留
    // 处理函数指针 (IDA offset 24)
    using HandlerFunc = int (*)(CFdScanner*, int, int, CStatus*);
    HandlerFunc handler;        // 帧类型处理函数
    uint32_t reserved6;         // 保留
    uint32_t reserved7;         // 保留
};

// ============================================================
// FrameHandlers - 帧处理器命名空间
// ============================================================
namespace FrameHandlers {

// 处理 Frame "TYPE" "NAME" { ... } 语句
int HandleFrame(CFdScanner* scanner, int stringHash, int frameHash, CStatus* status);

// 处理 Texture { ... } 子节点
int HandleTexture(CFdScanner* scanner, int stringHash, int frameHash, CStatus* status);

// 处理 SetPoint 锚点属性
int HandleSetPoint(CFdScanner* scanner, FdfNode* frame, CStatus* status);

// 处理 SetAllPoints 属性
int HandleSetAllPoints(CFdScanner* scanner, FdfNode* frame, CStatus* status);

// 处理 IncludeFile 指令
int HandleIncludeFile(CFdScanner* scanner, int stringHash, int frameHash, CStatus* status);

// 处理通用属性
int HandleProperty(CFdScanner* scanner, FdfNode* frame, CStatus* status, const std::string& propName);

// 注册所有帧类型处理器
bool RegisterAllHandlers();

// 清理处理器
void CleanupHandlers();

// 初始化默认处理器
void InitializeDefaultHandlers();

} // namespace FrameHandlers
