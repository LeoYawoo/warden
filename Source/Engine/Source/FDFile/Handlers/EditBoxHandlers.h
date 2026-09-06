#pragma once
// EditBoxHandlers.h - 编辑框处理器接口
// 基于 IDA 反编译分析实现
// 原始文件: Engine/Source/FDFile/Handlers/EditBoxHandlers.cpp

#include <cstdint>

// 前向声明
class CFdScanner;
class CStatus;
struct FdfNode;

// ============================================================
// EditBoxHandlers - 编辑框处理器命名空间
// 处理 EDITBOX 类型帧的属性
// ============================================================
namespace EditBoxHandlers {

// 处理编辑框属性
int HandleEditBoxProperties(CFdScanner* scanner, FdfNode* frame, CStatus* status);

// 处理 Password 属性
int HandlePassword(CFdScanner* scanner, FdfNode* frame, CStatus* status);

// 处理 EditMaxChars 属性
int HandleMaxLetters(CFdScanner* scanner, FdfNode* frame, CStatus* status);

// 处理 EditText 属性
int HandleEditText(CFdScanner* scanner, FdfNode* frame, CStatus* status);

// 处理 FontString 属性
int HandleFontString(CFdScanner* scanner, FdfNode* frame, CStatus* status);

// 处理 EditTextColor 属性
int HandleEditTextColor(CFdScanner* scanner, FdfNode* frame, CStatus* status);

// 处理 EditTextOffset 属性
int HandleEditTextOffset(CFdScanner* scanner, FdfNode* frame, CStatus* status);

// 处理 EditBorderSize 属性
int HandleEditBorderSize(CFdScanner* scanner, FdfNode* frame, CStatus* status);

// 处理 EditCursorColor 属性
int HandleEditCursorColor(CFdScanner* scanner, FdfNode* frame, CStatus* status);

} // namespace EditBoxHandlers
