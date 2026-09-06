#include "TextFrameHandlers.h"
#include "../FDFile.h"
#include <cstring>

// TextFrameHandlers.cpp - 文本帧处理器实现
// 基于 IDA 反编译分析实现
// 原始文件: Engine/Source/FDFile/Handlers/TextFrameHandlers.cpp
//
// IDA 关键函数:
// - sub_64359A: TEXT 构造函数 (type 5, size 0x110)

// ============================================================
// 文本帧属性关键字 (基于 IDA 字符串 7409684-7413000)
// ============================================================

// 对齐关键字
static const char* s_justifyH[] = {
    "JUSTIFYLEFT", "JUSTIFYCENTER", "JUSTIFYRIGHT", nullptr
};

static const char* s_justifyV[] = {
    "JUSTIFYTOP", "JUSTIFYMIDDLE", "JUSTIFYBOTTOM", nullptr
};

namespace TextFrameHandlers {

// ============================================================
// 处理文本帧属性
// IDA: sub_64359A 内部属性处理
// ============================================================
int HandleTextProperties(CFdScanner* scanner, FdfNode* frame, CStatus* status) {
    // TEXT 类型帧属性:
    // - Text: 显示文本
    // - FontColor: 字体颜色 (RGBA)
    // - FontHeight: 字体高度
    // - FontJustificationH: 水平对齐
    // - FontJustificationV: 垂直对齐
    // - FontJustificationOffset: 对齐偏移
    // - FontShadowColor: 阴影颜色
    // - FontShadowOffset: 阴影偏移
    // - FontHighlightColor: 高亮颜色
    // - FontDisabledColor: 禁用颜色
    // - FontFlags: 字体标志
    // - FontCharSpacing: 字符间距

    if (!scanner || !frame) return 0;

    // 通用属性处理器会处理这些属性
    return 1;
}

// ============================================================
// 处理 Text 属性
// ============================================================
int HandleText(CFdScanner* scanner, FdfNode* frame, CStatus* status) {
    // Text "BNET_REALM_SELECT"
    // 设置显示文本

    if (!scanner || !frame) return 0;

    FdfAttribute attr;
    attr.name = "Text";

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
// 处理 FontColor 属性
// ============================================================
int HandleFontColor(CFdScanner* scanner, FdfNode* frame, CStatus* status) {
    // FontColor 1.0 1.0 1.0 1.0
    // 设置字体颜色 (R G B A)

    if (!scanner || !frame) return 0;

    FdfAttribute attr;
    attr.name = "FontColor";

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
// 处理 FontJustificationH 属性
// ============================================================
int HandleFontJustificationH(CFdScanner* scanner, FdfNode* frame, CStatus* status) {
    // FontJustificationH JUSTIFYLEFT
    // FontJustificationH JUSTIFYCENTER
    // FontJustificationH JUSTIFYRIGHT

    if (!scanner || !frame) return 0;

    FdfAttribute attr;
    attr.name = "FontJustificationH";
    attr.value = scanner->NextToken(); // JUSTIFYLEFT, JUSTIFYCENTER, JUSTIFYRIGHT

    frame->attributes.push_back(attr);
    return 1;
}

// ============================================================
// 处理 FontJustificationV 属性
// ============================================================
int HandleFontJustificationV(CFdScanner* scanner, FdfNode* frame, CStatus* status) {
    // FontJustificationV JUSTIFYTOP
    // FontJustificationV JUSTIFYMIDDLE
    // FontJustificationV JUSTIFYBOTTOM

    if (!scanner || !frame) return 0;

    FdfAttribute attr;
    attr.name = "FontJustificationV";
    attr.value = scanner->NextToken(); // JUSTIFYTOP, JUSTIFYMIDDLE, JUSTIFYBOTTOM

    frame->attributes.push_back(attr);
    return 1;
}

// ============================================================
// 处理 FontHeight 属性
// ============================================================
int HandleFontHeight(CFdScanner* scanner, FdfNode* frame, CStatus* status) {
    // FontHeight 0.012
    // 设置字体高度

    if (!scanner || !frame) return 0;

    FdfAttribute attr;
    attr.name = "FontHeight";
    attr.value = scanner->NextToken();

    frame->attributes.push_back(attr);
    return 1;
}

// ============================================================
// 处理 FontJustificationOffset 属性
// ============================================================
int HandleFontJustificationOffset(CFdScanner* scanner, FdfNode* frame, CStatus* status) {
    // FontJustificationOffset 0.0 0.0
    // 设置对齐偏移 (X, Y)

    if (!scanner || !frame) return 0;

    FdfAttribute attr;
    attr.name = "FontJustificationOffset";

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
// 处理 FontShadowColor 属性
// ============================================================
int HandleFontShadowColor(CFdScanner* scanner, FdfNode* frame, CStatus* status) {
    // FontShadowColor 0.0 0.0 0.0 1.0
    // 设置阴影颜色

    if (!scanner || !frame) return 0;

    FdfAttribute attr;
    attr.name = "FontShadowColor";

    for (int i = 0; i < 4; i++) {
        std::string token = scanner->NextToken();
        attr.args.push_back(token);
        token = scanner->PeekToken();
        if (token == ",") scanner->NextToken();
    }

    frame->attributes.push_back(attr);
    return 1;
}

// ============================================================
// 处理 FontShadowOffset 属性
// ============================================================
int HandleFontShadowOffset(CFdScanner* scanner, FdfNode* frame, CStatus* status) {
    // FontShadowOffset 0.001 -0.001
    // 设置阴影偏移

    if (!scanner || !frame) return 0;

    FdfAttribute attr;
    attr.name = "FontShadowOffset";

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
// 处理 FontFlags 属性
// ============================================================
int HandleFontFlags(CFdScanner* scanner, FdfNode* frame, CStatus* status) {
    // FontFlags NONE
    // 设置字体标志

    if (!scanner || !frame) return 0;

    FdfAttribute attr;
    attr.name = "FontFlags";
    attr.value = scanner->NextToken();

    frame->attributes.push_back(attr);
    return 1;
}

// ============================================================
// 处理 FontCharSpacing 属性
// ============================================================
int HandleFontCharSpacing(CFdScanner* scanner, FdfNode* frame, CStatus* status) {
    // FontCharSpacing 0.0
    // 设置字符间距

    if (!scanner || !frame) return 0;

    FdfAttribute attr;
    attr.name = "FontCharSpacing";
    attr.value = scanner->NextToken();

    frame->attributes.push_back(attr);
    return 1;
}

} // namespace TextFrameHandlers
