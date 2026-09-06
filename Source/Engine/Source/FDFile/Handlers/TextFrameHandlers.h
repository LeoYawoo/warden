#pragma once
// TextFrameHandlers.h - 文本帧处理器接口
// 基于 IDA 反编译分析实现
// 原始文件: Engine/Source/FDFile/Handlers/TextFrameHandlers.cpp

#include <cstdint>

// 前向声明
class CFdScanner;
class CStatus;
struct FdfNode;

// ============================================================
// TextFrameHandlers - 文本帧处理器命名空间
// 处理 TEXT 类型帧的属性
// ============================================================
namespace TextFrameHandlers {

// 处理文本帧属性
int HandleTextProperties(CFdScanner* scanner, FdfNode* frame, CStatus* status);

// 处理 Text 属性
int HandleText(CFdScanner* scanner, FdfNode* frame, CStatus* status);

// 处理 FontColor 属性
int HandleFontColor(CFdScanner* scanner, FdfNode* frame, CStatus* status);

// 处理 FontJustificationH 属性
int HandleFontJustificationH(CFdScanner* scanner, FdfNode* frame, CStatus* status);

// 处理 FontJustificationV 属性
int HandleFontJustificationV(CFdScanner* scanner, FdfNode* frame, CStatus* status);

// 处理 FontHeight 属性
int HandleFontHeight(CFdScanner* scanner, FdfNode* frame, CStatus* status);

// 处理 FontJustificationOffset 属性
int HandleFontJustificationOffset(CFdScanner* scanner, FdfNode* frame, CStatus* status);

// 处理 FontShadowColor 属性
int HandleFontShadowColor(CFdScanner* scanner, FdfNode* frame, CStatus* status);

// 处理 FontShadowOffset 属性
int HandleFontShadowOffset(CFdScanner* scanner, FdfNode* frame, CStatus* status);

// 处理 FontFlags 属性
int HandleFontFlags(CFdScanner* scanner, FdfNode* frame, CStatus* status);

// 处理 FontCharSpacing 属性
int HandleFontCharSpacing(CFdScanner* scanner, FdfNode* frame, CStatus* status);

} // namespace TextFrameHandlers
