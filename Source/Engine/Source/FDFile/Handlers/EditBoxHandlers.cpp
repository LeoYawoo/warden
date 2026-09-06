#include "EditBoxHandlers.h"
#include "../FDFile.h"
#include <cstring>

// EditBoxHandlers.cpp - 编辑框处理器实现
// 基于 IDA 反编译分析实现
// 原始文件: Engine/Source/FDFile/Handlers/EditBoxHandlers.cpp
//
// IDA 关键函数:
// - sub_642DE0: EDITBOX 构造函数 (type 12, size 0x118)
// - sub_63F23E: MULTILINE_EDITBOX 构造函数 (type 13, size 0x200)

// ============================================================
// 编辑框属性关键字 (基于 IDA 字符串 7409684-7413000)
// ============================================================
static const char* s_editBoxProperties[] = {
    "Password",
    "EditMaxChars",
    "EditText",
    "EditTextColor",
    "EditTextOffset",
    "EditTextFrame",
    "EditTextHeight",
    "EditBorderSize",
    "EditCursorColor",
    "EditSetFocus",
    "EditHighlightInitial",
    "EditHighlightColor",
    nullptr
};

namespace EditBoxHandlers {

// ============================================================
// 处理编辑框属性
// IDA: sub_642DE0 内部属性处理
// ============================================================
int HandleEditBoxProperties(CFdScanner* scanner, FdfNode* frame, CStatus* status) {
    // 编辑框特有属性:
    // - Password: 是否密码输入框
    // - EditMaxChars: 最大字符数
    // - EditText: 默认文本
    // - EditTextColor: 文本颜色
    // - EditTextOffset: 文本偏移
    // - EditTextFrame: 文本帧
    // - EditTextHeight: 文本高度
    // - EditBorderSize: 边框大小
    // - EditCursorColor: 光标颜色
    // - EditSetFocus: 初始获得焦点
    // - EditHighlightInitial: 初始高亮
    // - EditHighlightColor: 高亮颜色

    if (!scanner || !frame) return 0;

    // 通用属性处理器会处理这些属性
    return 1;
}

// ============================================================
// 处理 Password 属性
// ============================================================
int HandlePassword(CFdScanner* scanner, FdfNode* frame, CStatus* status) {
    // Password
    // 标记此编辑框为密码输入框

    if (!frame) return 0;

    FdfAttribute attr;
    attr.name = "Password";
    attr.value = "1"; // 标记为密码框
    frame->attributes.push_back(attr);

    return 1;
}

// ============================================================
// 处理 EditMaxChars 属性
// ============================================================
int HandleMaxLetters(CFdScanner* scanner, FdfNode* frame, CStatus* status) {
    // EditMaxChars 32
    // 设置最大字符数

    if (!scanner || !frame) return 0;

    FdfAttribute attr;
    attr.name = "EditMaxChars";
    attr.value = scanner->NextToken(); // 读取数字

    frame->attributes.push_back(attr);
    return 1;
}

// ============================================================
// 处理 EditText 属性
// ============================================================
int HandleEditText(CFdScanner* scanner, FdfNode* frame, CStatus* status) {
    // EditText "Default Text"
    // 设置默认文本

    if (!scanner || !frame) return 0;

    FdfAttribute attr;
    attr.name = "EditText";

    // 检查是否是字符串字面量
    std::string token = scanner->PeekToken();
    if (!token.empty() && token[0] == '"') {
        attr.value = scanner->ReadStringLiteral();
    } else {
        attr.value = scanner->NextToken();
    }

    frame->attributes.push_back(attr);
    return 1;
}

// ============================================================
// 处理 FontString 属性
// ============================================================
int HandleFontString(CFdScanner* scanner, FdfNode* frame, CStatus* status) {
    // FontString "FontName"
    // 设置编辑框使用的字体

    if (!scanner || !frame) return 0;

    FdfAttribute attr;
    attr.name = "FontString";

    std::string token = scanner->PeekToken();
    if (!token.empty() && token[0] == '"') {
        attr.value = scanner->ReadStringLiteral();
    } else {
        attr.value = scanner->NextToken();
    }

    frame->attributes.push_back(attr);
    return 1;
}

// ============================================================
// 处理 EditTextColor 属性
// ============================================================
int HandleEditTextColor(CFdScanner* scanner, FdfNode* frame, CStatus* status) {
    // EditTextColor 1.0 1.0 1.0 1.0
    // 设置文本颜色 (RGBA)

    if (!scanner || !frame) return 0;

    FdfAttribute attr;
    attr.name = "EditTextColor";

    // 读取 R G B A 四个值
    for (int i = 0; i < 4; i++) {
        std::string token = scanner->NextToken();
        attr.args.push_back(token);
        // 跳过逗号
        token = scanner->PeekToken();
        if (token == ",") scanner->NextToken();
    }

    frame->attributes.push_back(attr);
    return 1;
}

// ============================================================
// 处理 EditTextOffset 属性
// ============================================================
int HandleEditTextOffset(CFdScanner* scanner, FdfNode* frame, CStatus* status) {
    // EditTextOffset 0.01 0.01
    // 设置文本偏移 (X, Y)

    if (!scanner || !frame) return 0;

    FdfAttribute attr;
    attr.name = "EditTextOffset";

    // 读取 X Y 两个值
    for (int i = 0; i < 2; i++) {
        std::string token = scanner->NextToken();
        attr.args.push_back(token);
        token = scanner->PeekToken();
        if (token == ",") scanner->NextToken();
    }

    frame->attributes.push_back(attr);
    return 1;
}

// ============================================================
// 处理 EditBorderSize 属性
// ============================================================
int HandleEditBorderSize(CFdScanner* scanner, FdfNode* frame, CStatus* status) {
    // EditBorderSize 0.005
    // 设置边框大小

    if (!scanner || !frame) return 0;

    FdfAttribute attr;
    attr.name = "EditBorderSize";
    attr.value = scanner->NextToken();

    frame->attributes.push_back(attr);
    return 1;
}

// ============================================================
// 处理 EditCursorColor 属性
// ============================================================
int HandleEditCursorColor(CFdScanner* scanner, FdfNode* frame, CStatus* status) {
    // EditCursorColor 1.0 1.0 1.0 1.0
    // 设置光标颜色

    if (!scanner || !frame) return 0;

    FdfAttribute attr;
    attr.name = "EditCursorColor";

    for (int i = 0; i < 4; i++) {
        std::string token = scanner->NextToken();
        attr.args.push_back(token);
        token = scanner->PeekToken();
        if (token == ",") scanner->NextToken();
    }

    frame->attributes.push_back(attr);
    return 1;
}

} // namespace EditBoxHandlers
