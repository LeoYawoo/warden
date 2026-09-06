#pragma once
// FrameHandlers.h - 帧处理器接口
// 基于 IDA 反编译分析实现
// 原始文件: Engine/Source/FDFile/Handlers/FrameHandlers.cpp

#include <cstdint>
#include <string>
#include "HandlerHash.h"

// 前向声明
class CFdScanner;
class CStatus;
struct FdfNode;
struct FdfAttribute;

// ============================================================
// FrameHandlers - 帧处理器命名空间
// ============================================================
namespace FrameHandlers {

// 注册所有帧类型处理器
bool RegisterAllHandlers();

// 清理处理器
void CleanupHandlers();

// 初始化默认处理器
void InitializeDefaultHandlers();

} // namespace FrameHandlers
