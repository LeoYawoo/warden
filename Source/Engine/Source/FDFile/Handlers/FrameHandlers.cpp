#include "FrameHandlers.h"
#include "HandlerHash.h"
#include "../FDFile.h"
#include <cstring>

// FrameHandlers.cpp - 帧处理器实现
// 基于 IDA 反编译分析实现
//
// IDA 架构:
// CFdScanner 读取 token → HANDLERHASH 查找 → 调用处理函数
//
// 关键函数:
// - sub_1F571E: 注册处理器到 HANDLERHASH
// - sub_1F5634: 初始化默认处理器

// ============================================================
// 前向声明 - 处理函数
// ============================================================
static int HandleFrame(CFdScanner* scanner, int stringHash, int frameHash, CStatus* status);
static int HandleStringList(CFdScanner* scanner, int stringHash, int frameHash, CStatus* status);
static int HandleIncludeFile(CFdScanner* scanner, int stringHash, int frameHash, CStatus* status);
static int HandleTexture(CFdScanner* scanner, int stringHash, int frameHash, CStatus* status);
static int HandleSetPoint(CFdScanner* scanner, int stringHash, int frameHash, CStatus* status);
static int HandleSetAllPoints(CFdScanner* scanner, int stringHash, int frameHash, CStatus* status);
static int HandleInherits(CFdScanner* scanner, int stringHash, int frameHash, CStatus* status);
static int HandleWidth(CFdScanner* scanner, int stringHash, int frameHash, CStatus* status);
static int HandleHeight(CFdScanner* scanner, int stringHash, int frameHash, CStatus* status);
static int HandleAnchor(CFdScanner* scanner, int stringHash, int frameHash, CStatus* status);
static int HandleText(CFdScanner* scanner, int stringHash, int frameHash, CStatus* status);
static int HandleFontColor(CFdScanner* scanner, int stringHash, int frameHash, CStatus* status);
static int HandleFontJustificationH(CFdScanner* scanner, int stringHash, int frameHash, CStatus* status);
static int HandleFontJustificationV(CFdScanner* scanner, int stringHash, int frameHash, CStatus* status);
static int HandleFontHeight(CFdScanner* scanner, int stringHash, int frameHash, CStatus* status);
static int HandleFile(CFdScanner* scanner, int stringHash, int frameHash, CStatus* status);
static int HandleTexCoord(CFdScanner* scanner, int stringHash, int frameHash, CStatus* status);
static int HandleAlphaMode(CFdScanner* scanner, int stringHash, int frameHash, CStatus* status);
static int HandleBackgroundArt(CFdScanner* scanner, int stringHash, int frameHash, CStatus* status);
static int HandleBackdropBackground(CFdScanner* scanner, int stringHash, int frameHash, CStatus* status);
static int HandleBackdropTileBackground(CFdScanner* scanner, int stringHash, int frameHash, CStatus* status);
static int HandleBackdropCornerFlags(CFdScanner* scanner, int stringHash, int frameHash, CStatus* status);
static int HandleBackdropCornerFile(CFdScanner* scanner, int stringHash, int frameHash, CStatus* status);
static int HandleBackdropCornerSize(CFdScanner* scanner, int stringHash, int frameHash, CStatus* status);
static int HandleBackdropLeftFile(CFdScanner* scanner, int stringHash, int frameHash, CStatus* status);
static int HandleBackdropRightFile(CFdScanner* scanner, int stringHash, int frameHash, CStatus* status);
static int HandleBackdropTopFile(CFdScanner* scanner, int stringHash, int frameHash, CStatus* status);
static int HandleBackdropBottomFile(CFdScanner* scanner, int stringHash, int frameHash, CStatus* status);
static int HandleBackdropHalfSides(CFdScanner* scanner, int stringHash, int frameHash, CStatus* status);
static int HandleBackdropBlendAll(CFdScanner* scanner, int stringHash, int frameHash, CStatus* status);
static int HandleBackdropMirrored(CFdScanner* scanner, int stringHash, int frameHash, CStatus* status);
static int HandleButtonText(CFdScanner* scanner, int stringHash, int frameHash, CStatus* status);
static int HandleControlShortcutKey(CFdScanner* scanner, int stringHash, int frameHash, CStatus* status);
static int HandleControlArt(CFdScanner* scanner, int stringHash, int frameHash, CStatus* status);
static int HandleControlStyle(CFdScanner* scanner, int stringHash, int frameHash, CStatus* status);
static int HandleControlBackdrop(CFdScanner* scanner, int stringHash, int frameHash, CStatus* status);
static int HandleControlFocusHighlight(CFdScanner* scanner, int stringHash, int frameHash, CStatus* status);
static int HandleControlMouseOverHighlight(CFdScanner* scanner, int stringHash, int frameHash, CStatus* status);
static int HandlePassword(CFdScanner* scanner, int stringHash, int frameHash, CStatus* status);
static int HandleEditMaxChars(CFdScanner* scanner, int stringHash, int frameHash, CStatus* status);
static int HandleEditText(CFdScanner* scanner, int stringHash, int frameHash, CStatus* status);
static int HandleEditTextColor(CFdScanner* scanner, int stringHash, int frameHash, CStatus* status);
static int HandleEditTextOffset(CFdScanner* scanner, int stringHash, int frameHash, CStatus* status);
static int HandleEditTextFrame(CFdScanner* scanner, int stringHash, int frameHash, CStatus* status);
static int HandleEditTextHeight(CFdScanner* scanner, int stringHash, int frameHash, CStatus* status);
static int HandleEditBorderSize(CFdScanner* scanner, int stringHash, int frameHash, CStatus* status);
static int HandleEditCursorColor(CFdScanner* scanner, int stringHash, int frameHash, CStatus* status);
static int HandleEditSetFocus(CFdScanner* scanner, int stringHash, int frameHash, CStatus* status);
static int HandleHitRectInsets(CFdScanner* scanner, int stringHash, int frameHash, CStatus* status);
static int HandleToolTip(CFdScanner* scanner, int stringHash, int frameHash, CStatus* status);
static int HandleShortcutKey(CFdScanner* scanner, int stringHash, int frameHash, CStatus* status);
static int HandleTabFocusDefault(CFdScanner* scanner, int stringHash, int frameHash, CStatus* status);
static int HandleTabFocusNext(CFdScanner* scanner, int stringHash, int frameHash, CStatus* status);
static int HandleTabFocusPush(CFdScanner* scanner, int stringHash, int frameHash, CStatus* status);
static int HandleDecorateFileNames(CFdScanner* scanner, int stringHash, int frameHash, CStatus* status);
static int HandleDoNotRegisterName(CFdScanner* scanner, int stringHash, int frameHash, CStatus* status);
static int HandleLayer(CFdScanner* scanner, int stringHash, int frameHash, CStatus* status);
static int HandleLayerStyle(CFdScanner* scanner, int stringHash, int frameHash, CStatus* status);
static int HandleDisabledTexture(CFdScanner* scanner, int stringHash, int frameHash, CStatus* status);
static int HandleNormalTexture(CFdScanner* scanner, int stringHash, int frameHash, CStatus* status);
static int HandlePushedTexture(CFdScanner* scanner, int stringHash, int frameHash, CStatus* status);
static int HandleCheckedTexture(CFdScanner* scanner, int stringHash, int frameHash, CStatus* status);
static int HandleBarTexture(CFdScanner* scanner, int stringHash, int frameHash, CStatus* status);
static int HandleDisabledText(CFdScanner* scanner, int stringHash, int frameHash, CStatus* status);
static int HandleNormalText(CFdScanner* scanner, int stringHash, int frameHash, CStatus* status);
static int HandleHighlightText(CFdScanner* scanner, int stringHash, int frameHash, CStatus* status);
static int HandleSliderMinValue(CFdScanner* scanner, int stringHash, int frameHash, CStatus* status);
static int HandleSliderMaxValue(CFdScanner* scanner, int stringHash, int frameHash, CStatus* status);
static int HandleSliderStepSize(CFdScanner* scanner, int stringHash, int frameHash, CStatus* status);
static int HandleSliderInitialValue(CFdScanner* scanner, int stringHash, int frameHash, CStatus* status);
static int HandleSliderBackdropFrame(CFdScanner* scanner, int stringHash, int frameHash, CStatus* status);
static int HandleSliderThumbButtonFrame(CFdScanner* scanner, int stringHash, int frameHash, CStatus* status);
static int HandleDialogBackdrop(CFdScanner* scanner, int stringHash, int frameHash, CStatus* status);
static int HandleDialogOkButton(CFdScanner* scanner, int stringHash, int frameHash, CStatus* status);
static int HandleDialogCancelButton(CFdScanner* scanner, int stringHash, int frameHash, CStatus* status);
static int HandleListBoxBorder(CFdScanner* scanner, int stringHash, int frameHash, CStatus* status);
static int HandleListBoxStyle(CFdScanner* scanner, int stringHash, int frameHash, CStatus* status);
static int HandleListBoxItemHeight(CFdScanner* scanner, int stringHash, int frameHash, CStatus* status);
static int HandleListBoxScrollBar(CFdScanner* scanner, int stringHash, int frameHash, CStatus* status);
static int HandleSelectedColor(CFdScanner* scanner, int stringHash, int frameHash, CStatus* status);
static int HandleFocusColor(CFdScanner* scanner, int stringHash, int frameHash, CStatus* status);
static int HandleMenuItemHeight(CFdScanner* scanner, int stringHash, int frameHash, CStatus* status);
static int HandleMenuTextHighlightColor(CFdScanner* scanner, int stringHash, int frameHash, CStatus* status);
static int HandleMenuFontHeight(CFdScanner* scanner, int stringHash, int frameHash, CStatus* status);
static int HandleMenuBorder(CFdScanner* scanner, int stringHash, int frameHash, CStatus* status);
static int HandleMenuItem(CFdScanner* scanner, int stringHash, int frameHash, CStatus* status);

namespace FrameHandlers {

// ============================================================
// IDA: sub_1F5634 - 初始化默认处理器
// ============================================================
void InitializeDefaultHandlers() {
    // IDA 中的流程:
    // 遍历 unk_E77DE0 数组，创建 HANDLERHASH 节点
    // 这里我们使用简化实现
}

// ============================================================
// IDA: sub_1F571E - 注册处理器
// ============================================================
bool RegisterAllHandlers() {
    HandlerHash& hash = GlobalHandlers::GetHandlerHash();

    // 注册顶级关键字处理器
    hash.Register("Frame", HandleFrame);
    hash.Register("StringList", HandleStringList);
    hash.Register("IncludeFile", HandleIncludeFile);
    hash.Register("Texture", HandleTexture);

    // 注册属性处理器
    hash.Register("SetPoint", HandleSetPoint);
    hash.Register("SetAllPoints", HandleSetAllPoints);
    hash.Register("INHERITS", HandleInherits);
    hash.Register("Width", HandleWidth);
    hash.Register("Height", HandleHeight);
    hash.Register("Anchor", HandleAnchor);

    // 文本属性
    hash.Register("Text", HandleText);
    hash.Register("FontColor", HandleFontColor);
    hash.Register("FontJustificationH", HandleFontJustificationH);
    hash.Register("FontJustificationV", HandleFontJustificationV);
    hash.Register("FontHeight", HandleFontHeight);

    // 纹理属性
    hash.Register("File", HandleFile);
    hash.Register("TexCoord", HandleTexCoord);
    hash.Register("AlphaMode", HandleAlphaMode);
    hash.Register("BackgroundArt", HandleBackgroundArt);

    // 背景属性
    hash.Register("BackdropBackground", HandleBackdropBackground);
    hash.Register("BackdropTileBackground", HandleBackdropTileBackground);
    hash.Register("BackdropCornerFlags", HandleBackdropCornerFlags);
    hash.Register("BackdropCornerFile", HandleBackdropCornerFile);
    hash.Register("BackdropCornerSize", HandleBackdropCornerSize);
    hash.Register("BackdropLeftFile", HandleBackdropLeftFile);
    hash.Register("BackdropRightFile", HandleBackdropRightFile);
    hash.Register("BackdropTopFile", HandleBackdropTopFile);
    hash.Register("BackdropBottomFile", HandleBackdropBottomFile);
    hash.Register("BackdropHalfSides", HandleBackdropHalfSides);
    hash.Register("BackdropBlendAll", HandleBackdropBlendAll);
    hash.Register("BackdropMirrored", HandleBackdropMirrored);

    // 按钮属性
    hash.Register("ButtonText", HandleButtonText);
    hash.Register("ControlShortcutKey", HandleControlShortcutKey);
    hash.Register("ControlArt", HandleControlArt);
    hash.Register("ControlStyle", HandleControlStyle);
    hash.Register("ControlBackdrop", HandleControlBackdrop);
    hash.Register("ControlFocusHighlight", HandleControlFocusHighlight);
    hash.Register("ControlMouseOverHighlight", HandleControlMouseOverHighlight);

    // 编辑框属性
    hash.Register("Password", HandlePassword);
    hash.Register("EditMaxChars", HandleEditMaxChars);
    hash.Register("EditText", HandleEditText);
    hash.Register("EditTextColor", HandleEditTextColor);
    hash.Register("EditTextOffset", HandleEditTextOffset);
    hash.Register("EditTextFrame", HandleEditTextFrame);
    hash.Register("EditTextHeight", HandleEditTextHeight);
    hash.Register("EditBorderSize", HandleEditBorderSize);
    hash.Register("EditCursorColor", HandleEditCursorColor);
    hash.Register("EditSetFocus", HandleEditSetFocus);

    // 其他属性
    hash.Register("HitRectInsets", HandleHitRectInsets);
    hash.Register("ToolTip", HandleToolTip);
    hash.Register("ShortcutKey", HandleShortcutKey);
    hash.Register("TabFocusDefault", HandleTabFocusDefault);
    hash.Register("TabFocusNext", HandleTabFocusNext);
    hash.Register("TabFocusPush", HandleTabFocusPush);
    hash.Register("DecorateFileNames", HandleDecorateFileNames);
    hash.Register("DoNotRegisterName", HandleDoNotRegisterName);
    hash.Register("Layer", HandleLayer);
    hash.Register("LayerStyle", HandleLayerStyle);

    // 纹理属性
    hash.Register("DisabledTexture", HandleDisabledTexture);
    hash.Register("NormalTexture", HandleNormalTexture);
    hash.Register("PushedTexture", HandlePushedTexture);
    hash.Register("CheckedTexture", HandleCheckedTexture);
    hash.Register("BarTexture", HandleBarTexture);
    hash.Register("DisabledText", HandleDisabledText);
    hash.Register("NormalText", HandleNormalText);
    hash.Register("HighlightText", HandleHighlightText);

    // 滑块属性
    hash.Register("SliderMinValue", HandleSliderMinValue);
    hash.Register("SliderMaxValue", HandleSliderMaxValue);
    hash.Register("SliderStepSize", HandleSliderStepSize);
    hash.Register("SliderInitialValue", HandleSliderInitialValue);
    hash.Register("SliderBackdropFrame", HandleSliderBackdropFrame);
    hash.Register("SliderThumbButtonFrame", HandleSliderThumbButtonFrame);

    // 对话框属性
    hash.Register("DialogBackdrop", HandleDialogBackdrop);
    hash.Register("DialogOkButton", HandleDialogOkButton);
    hash.Register("DialogCancelButton", HandleDialogCancelButton);

    // 列表框属性
    hash.Register("ListBoxBorder", HandleListBoxBorder);
    hash.Register("ListBoxStyle", HandleListBoxStyle);
    hash.Register("ListBoxItemHeight", HandleListBoxItemHeight);
    hash.Register("ListBoxScrollBar", HandleListBoxScrollBar);
    hash.Register("SelectedColor", HandleSelectedColor);
    hash.Register("FocusColor", HandleFocusColor);

    // 菜单属性
    hash.Register("MenuItemHeight", HandleMenuItemHeight);
    hash.Register("MenuTextHighlightColor", HandleMenuTextHighlightColor);
    hash.Register("MenuFontHeight", HandleMenuFontHeight);
    hash.Register("MenuBorder", HandleMenuBorder);
    hash.Register("MenuItem", HandleMenuItem);

    return true;
}

// ============================================================
// IDA: sub_1F55FE - 清理处理器
// ============================================================
void CleanupHandlers() {
    GlobalHandlers::GetHandlerHash().Clear();
}

} // namespace FrameHandlers

// ============================================================
// 处理函数实现
// ============================================================

// Frame "TYPE" "NAME" INHERITS "Template" { ... }
static int HandleFrame(CFdScanner* scanner, int, int, CStatus*) {
    if (!scanner) return 0;

    // 读取帧类型
    std::string frameType = scanner->NextToken();

    // 读取帧名称
    std::string frameName = scanner->NextToken();

    // 检查 INHERITS
    std::string token = scanner->PeekToken();
    std::string inheritsFrom;
    bool withChildren = false;
    if (token == "INHERITS") {
        scanner->NextToken();
        token = scanner->PeekToken();
        if (token == "WITHCHILDREN") {
            scanner->NextToken();
            withChildren = true;
        }
        inheritsFrom = scanner->NextToken();
    }

    // 读取左大括号
    token = scanner->NextToken();
    if (token != "{") return 0;

    // 创建帧节点
    FdfNode* frame = new FdfNode();
    frame->type = FDF_NODE_FRAME;
    frame->frameType = frameType;
    frame->name = frameName;
    frame->inheritsFrom = inheritsFrom;
    frame->withChildren = withChildren;

    // 解析帧体
    int depth = 1;
    while (scanner->HasMore() && depth > 0) {
        token = scanner->PeekToken();
        if (token.empty()) break;

        if (token == "}") {
            scanner->NextToken();
            depth--;
            continue;
        }

        if (token == "{") {
            scanner->NextToken();
            depth++;
            continue;
        }

        // 查找属性处理器
        HandlerHash& hash = GlobalHandlers::GetHandlerHash();
        FdfHandlerFunc handler = hash.Find(token);
        if (handler) {
            handler(scanner, 0, 0, nullptr);
        } else {
            // 未知属性，跳过
            scanner->NextToken();
        }
    }

    // 注册到全局帧表
    // 注意: 这里需要访问 FDFile 的成员，但当前架构无法直接访问
    // 实际实现中，这些信息会通过 handler 参数传递

    return 1;
}

// StringList { KEY "VALUE", }
static int HandleStringList(CFdScanner* scanner, int, int, CStatus*) {
    if (!scanner) return 0;

    std::string token = scanner->NextToken();
    if (token != "{") return 0;

    while (scanner->HasMore()) {
        token = scanner->PeekToken();
        if (token == "}") {
            scanner->NextToken();
            break;
        }
        if (token.empty()) break;

        // 读取键名
        std::string key = scanner->NextToken();

        // 读取字符串值
        std::string value;
        token = scanner->PeekToken();
        if (!token.empty() && token[0] == '"') {
            value = scanner->ReadStringLiteral();
        } else {
            value = scanner->NextToken();
        }

        // 跳过逗号
        token = scanner->PeekToken();
        if (token == ",") scanner->NextToken();

        // 存储字符串 (需要访问 FDFile 的成员)
        // 实际实现中会通过参数传递
    }

    return 1;
}

// IncludeFile "path.fdf"
static int HandleIncludeFile(CFdScanner* scanner, int, int, CStatus*) {
    if (!scanner) return 0;

    std::string path = scanner->NextToken();
    // 实际实现中会加载并解析文件
    return 1;
}

// Texture { ... }
static int HandleTexture(CFdScanner* scanner, int, int, CStatus*) {
    if (!scanner) return 0;

    std::string token = scanner->NextToken();
    if (token != "{") return 0;

    // 解析 Texture 属性
    while (scanner->HasMore()) {
        token = scanner->PeekToken();
        if (token == "}") {
            scanner->NextToken();
            break;
        }
        if (token.empty()) break;

        // 查找属性处理器
        HandlerHash& hash = GlobalHandlers::GetHandlerHash();
        FdfHandlerFunc handler = hash.Find(token);
        if (handler) {
            handler(scanner, 0, 0, nullptr);
        } else {
            scanner->NextToken();
        }
    }

    return 1;
}

// SetPoint TOPLEFT, "ParentFrame", TOPLEFT, 0.1, 0.2
static int HandleSetPoint(CFdScanner* scanner, int, int, CStatus*) {
    if (!scanner) return 0;

    // 读取锚点类型
    std::string anchor = scanner->NextToken();

    // 跳过逗号
    std::string token = scanner->NextToken(); // 逗号

    // 读取父帧名称
    std::string parent = scanner->NextToken();

    // 跳过逗号
    token = scanner->NextToken(); // 逗号

    // 读取父锚点
    std::string parentAnchor = scanner->NextToken();

    // 跳过逗号
    token = scanner->NextToken(); // 逗号

    // 读取 X 偏移
    std::string x = scanner->NextToken();

    // 跳过逗号
    token = scanner->NextToken(); // 逗号

    // 读取 Y 偏移
    std::string y = scanner->NextToken();

    return 1;
}

// SetAllPoints
static int HandleSetAllPoints(CFdScanner*, int, int, CStatus*) {
    return 1;
}

// INHERITS "Template"
static int HandleInherits(CFdScanner*, int, int, CStatus*) {
    return 1;
}

// Width 0.5
static int HandleWidth(CFdScanner* scanner, int, int, CStatus*) {
    if (!scanner) return 0;
    std::string value = scanner->NextToken();
    // 跳过逗号
    std::string token = scanner->PeekToken();
    if (token == ",") scanner->NextToken();
    return 1;
}

// Height 0.3
static int HandleHeight(CFdScanner* scanner, int, int, CStatus*) {
    if (!scanner) return 0;
    std::string value = scanner->NextToken();
    std::string token = scanner->PeekToken();
    if (token == ",") scanner->NextToken();
    return 1;
}

// Anchor TOPLEFT, 0, 0
static int HandleAnchor(CFdScanner* scanner, int, int, CStatus*) {
    if (!scanner) return 0;
    std::string anchor = scanner->NextToken();
    // 跳过逗号和参数
    while (scanner->HasMore()) {
        std::string token = scanner->PeekToken();
        if (token == "," || token == "}" || token == "Frame" || token == "Texture") break;
        scanner->NextToken();
    }
    return 1;
}

// Text "StringKey"
static int HandleText(CFdScanner* scanner, int, int, CStatus*) {
    if (!scanner) return 0;
    std::string value = scanner->NextToken();
    std::string token = scanner->PeekToken();
    if (token == ",") scanner->NextToken();
    return 1;
}

// FontColor 1.0 1.0 1.0 1.0
static int HandleFontColor(CFdScanner* scanner, int, int, CStatus*) {
    if (!scanner) return 0;
    for (int i = 0; i < 4; i++) {
        std::string token = scanner->NextToken();
        token = scanner->PeekToken();
        if (token == ",") scanner->NextToken();
    }
    return 1;
}

// FontJustificationH JUSTIFYLEFT
static int HandleFontJustificationH(CFdScanner* scanner, int, int, CStatus*) {
    if (!scanner) return 0;
    std::string value = scanner->NextToken();
    std::string token = scanner->PeekToken();
    if (token == ",") scanner->NextToken();
    return 1;
}

// FontJustificationV JUSTIFYTOP
static int HandleFontJustificationV(CFdScanner* scanner, int, int, CStatus*) {
    if (!scanner) return 0;
    std::string value = scanner->NextToken();
    std::string token = scanner->PeekToken();
    if (token == ",") scanner->NextToken();
    return 1;
}

// FontHeight 0.012
static int HandleFontHeight(CFdScanner* scanner, int, int, CStatus*) {
    if (!scanner) return 0;
    std::string value = scanner->NextToken();
    std::string token = scanner->PeekToken();
    if (token == ",") scanner->NextToken();
    return 1;
}

// File "path.blp"
static int HandleFile(CFdScanner* scanner, int, int, CStatus*) {
    if (!scanner) return 0;
    std::string value = scanner->NextToken();
    std::string token = scanner->PeekToken();
    if (token == ",") scanner->NextToken();
    return 1;
}

// TexCoord 0, 1, 0, 0.125
static int HandleTexCoord(CFdScanner* scanner, int, int, CStatus*) {
    if (!scanner) return 0;
    for (int i = 0; i < 4; i++) {
        std::string token = scanner->NextToken();
        token = scanner->PeekToken();
        if (token == ",") scanner->NextToken();
    }
    return 1;
}

// AlphaMode "ALPHAKEY"
static int HandleAlphaMode(CFdScanner* scanner, int, int, CStatus*) {
    if (!scanner) return 0;
    std::string value = scanner->NextToken();
    std::string token = scanner->PeekToken();
    if (token == ",") scanner->NextToken();
    return 1;
}

// BackgroundArt "path.mdl"
static int HandleBackgroundArt(CFdScanner* scanner, int, int, CStatus*) {
    if (!scanner) return 0;
    std::string value = scanner->NextToken();
    std::string token = scanner->PeekToken();
    if (token == ",") scanner->NextToken();
    return 1;
}

// BackdropBackground "path.blp"
static int HandleBackdropBackground(CFdScanner* scanner, int, int, CStatus*) {
    if (!scanner) return 0;
    std::string value = scanner->NextToken();
    std::string token = scanner->PeekToken();
    if (token == ",") scanner->NextToken();
    return 1;
}

// BackdropTileBackground
static int HandleBackdropTileBackground(CFdScanner*, int, int, CStatus*) {
    return 1;
}

// BackdropCornerFlags "UL|UR|BL|BR"
static int HandleBackdropCornerFlags(CFdScanner* scanner, int, int, CStatus*) {
    if (!scanner) return 0;
    std::string value = scanner->NextToken();
    std::string token = scanner->PeekToken();
    if (token == ",") scanner->NextToken();
    return 1;
}

// BackdropCornerFile "path.blp"
static int HandleBackdropCornerFile(CFdScanner* scanner, int, int, CStatus*) {
    if (!scanner) return 0;
    std::string value = scanner->NextToken();
    std::string token = scanner->PeekToken();
    if (token == ",") scanner->NextToken();
    return 1;
}

// BackdropCornerSize 0.015
static int HandleBackdropCornerSize(CFdScanner* scanner, int, int, CStatus*) {
    if (!scanner) return 0;
    std::string value = scanner->NextToken();
    std::string token = scanner->PeekToken();
    if (token == ",") scanner->NextToken();
    return 1;
}

// BackdropLeftFile "path.blp"
static int HandleBackdropLeftFile(CFdScanner* scanner, int, int, CStatus*) {
    if (!scanner) return 0;
    std::string value = scanner->NextToken();
    std::string token = scanner->PeekToken();
    if (token == ",") scanner->NextToken();
    return 1;
}

// BackdropRightFile "path.blp"
static int HandleBackdropRightFile(CFdScanner* scanner, int, int, CStatus*) {
    if (!scanner) return 0;
    std::string value = scanner->NextToken();
    std::string token = scanner->PeekToken();
    if (token == ",") scanner->NextToken();
    return 1;
}

// BackdropTopFile "path.blp"
static int HandleBackdropTopFile(CFdScanner* scanner, int, int, CStatus*) {
    if (!scanner) return 0;
    std::string value = scanner->NextToken();
    std::string token = scanner->PeekToken();
    if (token == ",") scanner->NextToken();
    return 1;
}

// BackdropBottomFile "path.blp"
static int HandleBackdropBottomFile(CFdScanner* scanner, int, int, CStatus*) {
    if (!scanner) return 0;
    std::string value = scanner->NextToken();
    std::string token = scanner->PeekToken();
    if (token == ",") scanner->NextToken();
    return 1;
}

// BackdropHalfSides
static int HandleBackdropHalfSides(CFdScanner*, int, int, CStatus*) {
    return 1;
}

// BackdropBlendAll
static int HandleBackdropBlendAll(CFdScanner*, int, int, CStatus*) {
    return 1;
}

// BackdropMirrored
static int HandleBackdropMirrored(CFdScanner*, int, int, CStatus*) {
    return 1;
}

// ButtonText "textName"
static int HandleButtonText(CFdScanner* scanner, int, int, CStatus*) {
    if (!scanner) return 0;
    std::string value = scanner->NextToken();
    std::string token = scanner->PeekToken();
    if (token == ",") scanner->NextToken();
    return 1;
}

// ControlShortcutKey "S"
static int HandleControlShortcutKey(CFdScanner* scanner, int, int, CStatus*) {
    if (!scanner) return 0;
    std::string value = scanner->NextToken();
    std::string token = scanner->PeekToken();
    if (token == ",") scanner->NextToken();
    return 1;
}

// ControlArt "path.blp"
static int HandleControlArt(CFdScanner* scanner, int, int, CStatus*) {
    if (!scanner) return 0;
    std::string value = scanner->NextToken();
    std::string token = scanner->PeekToken();
    if (token == ",") scanner->NextToken();
    return 1;
}

// ControlStyle "PUSHBUTTON"
static int HandleControlStyle(CFdScanner* scanner, int, int, CStatus*) {
    if (!scanner) return 0;
    std::string value = scanner->NextToken();
    std::string token = scanner->PeekToken();
    if (token == ",") scanner->NextToken();
    return 1;
}

// ControlBackdrop "frameName"
static int HandleControlBackdrop(CFdScanner* scanner, int, int, CStatus*) {
    if (!scanner) return 0;
    std::string value = scanner->NextToken();
    std::string token = scanner->PeekToken();
    if (token == ",") scanner->NextToken();
    return 1;
}

// ControlFocusHighlight "frameName"
static int HandleControlFocusHighlight(CFdScanner* scanner, int, int, CStatus*) {
    if (!scanner) return 0;
    std::string value = scanner->NextToken();
    std::string token = scanner->PeekToken();
    if (token == ",") scanner->NextToken();
    return 1;
}

// ControlMouseOverHighlight "frameName"
static int HandleControlMouseOverHighlight(CFdScanner* scanner, int, int, CStatus*) {
    if (!scanner) return 0;
    std::string value = scanner->NextToken();
    std::string token = scanner->PeekToken();
    if (token == ",") scanner->NextToken();
    return 1;
}

// Password
static int HandlePassword(CFdScanner*, int, int, CStatus*) {
    return 1;
}

// EditMaxChars 32
static int HandleEditMaxChars(CFdScanner* scanner, int, int, CStatus*) {
    if (!scanner) return 0;
    std::string value = scanner->NextToken();
    std::string token = scanner->PeekToken();
    if (token == ",") scanner->NextToken();
    return 1;
}

// EditText "default"
static int HandleEditText(CFdScanner* scanner, int, int, CStatus*) {
    if (!scanner) return 0;
    std::string value = scanner->NextToken();
    std::string token = scanner->PeekToken();
    if (token == ",") scanner->NextToken();
    return 1;
}

// EditTextColor 1.0 1.0 1.0 1.0
static int HandleEditTextColor(CFdScanner* scanner, int, int, CStatus*) {
    if (!scanner) return 0;
    for (int i = 0; i < 4; i++) {
        std::string token = scanner->NextToken();
        token = scanner->PeekToken();
        if (token == ",") scanner->NextToken();
    }
    return 1;
}

// EditTextOffset 0.01 0.01
static int HandleEditTextOffset(CFdScanner* scanner, int, int, CStatus*) {
    if (!scanner) return 0;
    for (int i = 0; i < 2; i++) {
        std::string token = scanner->NextToken();
        token = scanner->PeekToken();
        if (token == ",") scanner->NextToken();
    }
    return 1;
}

// EditTextFrame "frameName"
static int HandleEditTextFrame(CFdScanner* scanner, int, int, CStatus*) {
    if (!scanner) return 0;
    std::string value = scanner->NextToken();
    std::string token = scanner->PeekToken();
    if (token == ",") scanner->NextToken();
    return 1;
}

// EditTextHeight 0.02
static int HandleEditTextHeight(CFdScanner* scanner, int, int, CStatus*) {
    if (!scanner) return 0;
    std::string value = scanner->NextToken();
    std::string token = scanner->PeekToken();
    if (token == ",") scanner->NextToken();
    return 1;
}

// EditBorderSize 0.005
static int HandleEditBorderSize(CFdScanner* scanner, int, int, CStatus*) {
    if (!scanner) return 0;
    std::string value = scanner->NextToken();
    std::string token = scanner->PeekToken();
    if (token == ",") scanner->NextToken();
    return 1;
}

// EditCursorColor 1.0 1.0 1.0 1.0
static int HandleEditCursorColor(CFdScanner* scanner, int, int, CStatus*) {
    if (!scanner) return 0;
    for (int i = 0; i < 4; i++) {
        std::string token = scanner->NextToken();
        token = scanner->PeekToken();
        if (token == ",") scanner->NextToken();
    }
    return 1;
}

// EditSetFocus
static int HandleEditSetFocus(CFdScanner*, int, int, CStatus*) {
    return 1;
}

// HitRectInsets 0 0 0 0
static int HandleHitRectInsets(CFdScanner* scanner, int, int, CStatus*) {
    if (!scanner) return 0;
    for (int i = 0; i < 4; i++) {
        std::string token = scanner->NextToken();
        token = scanner->PeekToken();
        if (token == ",") scanner->NextToken();
    }
    return 1;
}

// ToolTip "text"
static int HandleToolTip(CFdScanner* scanner, int, int, CStatus*) {
    if (!scanner) return 0;
    std::string value = scanner->NextToken();
    std::string token = scanner->PeekToken();
    if (token == ",") scanner->NextToken();
    return 1;
}

// ShortcutKey "S"
static int HandleShortcutKey(CFdScanner* scanner, int, int, CStatus*) {
    if (!scanner) return 0;
    std::string value = scanner->NextToken();
    std::string token = scanner->PeekToken();
    if (token == ",") scanner->NextToken();
    return 1;
}

// TabFocusDefault
static int HandleTabFocusDefault(CFdScanner*, int, int, CStatus*) {
    return 1;
}

// TabFocusNext "frameName"
static int HandleTabFocusNext(CFdScanner* scanner, int, int, CStatus*) {
    if (!scanner) return 0;
    std::string value = scanner->NextToken();
    std::string token = scanner->PeekToken();
    if (token == ",") scanner->NextToken();
    return 1;
}

// TabFocusPush
static int HandleTabFocusPush(CFdScanner*, int, int, CStatus*) {
    return 1;
}

// DecorateFileNames
static int HandleDecorateFileNames(CFdScanner*, int, int, CStatus*) {
    return 1;
}

// DoNotRegisterName
static int HandleDoNotRegisterName(CFdScanner*, int, int, CStatus*) {
    return 1;
}

// Layer 0
static int HandleLayer(CFdScanner* scanner, int, int, CStatus*) {
    if (!scanner) return 0;
    std::string value = scanner->NextToken();
    std::string token = scanner->PeekToken();
    if (token == ",") scanner->NextToken();
    return 1;
}

// LayerStyle "LAYER"
static int HandleLayerStyle(CFdScanner* scanner, int, int, CStatus*) {
    if (!scanner) return 0;
    std::string value = scanner->NextToken();
    std::string token = scanner->PeekToken();
    if (token == ",") scanner->NextToken();
    return 1;
}

// DisabledTexture "path.blp"
static int HandleDisabledTexture(CFdScanner* scanner, int, int, CStatus*) {
    if (!scanner) return 0;
    std::string value = scanner->NextToken();
    std::string token = scanner->PeekToken();
    if (token == ",") scanner->NextToken();
    return 1;
}

// NormalTexture "path.blp"
static int HandleNormalTexture(CFdScanner* scanner, int, int, CStatus*) {
    if (!scanner) return 0;
    std::string value = scanner->NextToken();
    std::string token = scanner->PeekToken();
    if (token == ",") scanner->NextToken();
    return 1;
}

// PushedTexture "path.blp"
static int HandlePushedTexture(CFdScanner* scanner, int, int, CStatus*) {
    if (!scanner) return 0;
    std::string value = scanner->NextToken();
    std::string token = scanner->PeekToken();
    if (token == ",") scanner->NextToken();
    return 1;
}

// CheckedTexture "path.blp"
static int HandleCheckedTexture(CFdScanner* scanner, int, int, CStatus*) {
    if (!scanner) return 0;
    std::string value = scanner->NextToken();
    std::string token = scanner->PeekToken();
    if (token == ",") scanner->NextToken();
    return 1;
}

// BarTexture "path.blp"
static int HandleBarTexture(CFdScanner* scanner, int, int, CStatus*) {
    if (!scanner) return 0;
    std::string value = scanner->NextToken();
    std::string token = scanner->PeekToken();
    if (token == ",") scanner->NextToken();
    return 1;
}

// DisabledText "text"
static int HandleDisabledText(CFdScanner* scanner, int, int, CStatus*) {
    if (!scanner) return 0;
    std::string value = scanner->NextToken();
    std::string token = scanner->PeekToken();
    if (token == ",") scanner->NextToken();
    return 1;
}

// NormalText "text"
static int HandleNormalText(CFdScanner* scanner, int, int, CStatus*) {
    if (!scanner) return 0;
    std::string value = scanner->NextToken();
    std::string token = scanner->PeekToken();
    if (token == ",") scanner->NextToken();
    return 1;
}

// HighlightText "text"
static int HandleHighlightText(CFdScanner* scanner, int, int, CStatus*) {
    if (!scanner) return 0;
    std::string value = scanner->NextToken();
    std::string token = scanner->PeekToken();
    if (token == ",") scanner->NextToken();
    return 1;
}

// SliderMinValue 0
static int HandleSliderMinValue(CFdScanner* scanner, int, int, CStatus*) {
    if (!scanner) return 0;
    std::string value = scanner->NextToken();
    std::string token = scanner->PeekToken();
    if (token == ",") scanner->NextToken();
    return 1;
}

// SliderMaxValue 100
static int HandleSliderMaxValue(CFdScanner* scanner, int, int, CStatus*) {
    if (!scanner) return 0;
    std::string value = scanner->NextToken();
    std::string token = scanner->PeekToken();
    if (token == ",") scanner->NextToken();
    return 1;
}

// SliderStepSize 1
static int HandleSliderStepSize(CFdScanner* scanner, int, int, CStatus*) {
    if (!scanner) return 0;
    std::string value = scanner->NextToken();
    std::string token = scanner->PeekToken();
    if (token == ",") scanner->NextToken();
    return 1;
}

// SliderInitialValue 50
static int HandleSliderInitialValue(CFdScanner* scanner, int, int, CStatus*) {
    if (!scanner) return 0;
    std::string value = scanner->NextToken();
    std::string token = scanner->PeekToken();
    if (token == ",") scanner->NextToken();
    return 1;
}

// SliderBackdropFrame "frameName"
static int HandleSliderBackdropFrame(CFdScanner* scanner, int, int, CStatus*) {
    if (!scanner) return 0;
    std::string value = scanner->NextToken();
    std::string token = scanner->PeekToken();
    if (token == ",") scanner->NextToken();
    return 1;
}

// SliderThumbButtonFrame "frameName"
static int HandleSliderThumbButtonFrame(CFdScanner* scanner, int, int, CStatus*) {
    if (!scanner) return 0;
    std::string value = scanner->NextToken();
    std::string token = scanner->PeekToken();
    if (token == ",") scanner->NextToken();
    return 1;
}

// DialogBackdrop "frameName"
static int HandleDialogBackdrop(CFdScanner* scanner, int, int, CStatus*) {
    if (!scanner) return 0;
    std::string value = scanner->NextToken();
    std::string token = scanner->PeekToken();
    if (token == ",") scanner->NextToken();
    return 1;
}

// DialogOkButton "frameName"
static int HandleDialogOkButton(CFdScanner* scanner, int, int, CStatus*) {
    if (!scanner) return 0;
    std::string value = scanner->NextToken();
    std::string token = scanner->PeekToken();
    if (token == ",") scanner->NextToken();
    return 1;
}

// DialogCancelButton "frameName"
static int HandleDialogCancelButton(CFdScanner* scanner, int, int, CStatus*) {
    if (!scanner) return 0;
    std::string value = scanner->NextToken();
    std::string token = scanner->PeekToken();
    if (token == ",") scanner->NextToken();
    return 1;
}

// ListBoxBorder 0.01
static int HandleListBoxBorder(CFdScanner* scanner, int, int, CStatus*) {
    if (!scanner) return 0;
    std::string value = scanner->NextToken();
    std::string token = scanner->PeekToken();
    if (token == ",") scanner->NextToken();
    return 1;
}

// ListBoxStyle "LISTBOX"
static int HandleListBoxStyle(CFdScanner* scanner, int, int, CStatus*) {
    if (!scanner) return 0;
    std::string value = scanner->NextToken();
    std::string token = scanner->PeekToken();
    if (token == ",") scanner->NextToken();
    return 1;
}

// ListBoxItemHeight 0.02
static int HandleListBoxItemHeight(CFdScanner* scanner, int, int, CStatus*) {
    if (!scanner) return 0;
    std::string value = scanner->NextToken();
    std::string token = scanner->PeekToken();
    if (token == ",") scanner->NextToken();
    return 1;
}

// ListBoxScrollBar "frameName"
static int HandleListBoxScrollBar(CFdScanner* scanner, int, int, CStatus*) {
    if (!scanner) return 0;
    std::string value = scanner->NextToken();
    std::string token = scanner->PeekToken();
    if (token == ",") scanner->NextToken();
    return 1;
}

// SelectedColor 1.0 1.0 1.0 1.0
static int HandleSelectedColor(CFdScanner* scanner, int, int, CStatus*) {
    if (!scanner) return 0;
    for (int i = 0; i < 4; i++) {
        std::string token = scanner->NextToken();
        token = scanner->PeekToken();
        if (token == ",") scanner->NextToken();
    }
    return 1;
}

// FocusColor 1.0 1.0 1.0 1.0
static int HandleFocusColor(CFdScanner* scanner, int, int, CStatus*) {
    if (!scanner) return 0;
    for (int i = 0; i < 4; i++) {
        std::string token = scanner->NextToken();
        token = scanner->PeekToken();
        if (token == ",") scanner->NextToken();
    }
    return 1;
}

// MenuItemHeight 0.02
static int HandleMenuItemHeight(CFdScanner* scanner, int, int, CStatus*) {
    if (!scanner) return 0;
    std::string value = scanner->NextToken();
    std::string token = scanner->PeekToken();
    if (token == ",") scanner->NextToken();
    return 1;
}

// MenuTextHighlightColor 1.0 1.0 1.0 1.0
static int HandleMenuTextHighlightColor(CFdScanner* scanner, int, int, CStatus*) {
    if (!scanner) return 0;
    for (int i = 0; i < 4; i++) {
        std::string token = scanner->NextToken();
        token = scanner->PeekToken();
        if (token == ",") scanner->NextToken();
    }
    return 1;
}

// MenuFontHeight 0.012
static int HandleMenuFontHeight(CFdScanner* scanner, int, int, CStatus*) {
    if (!scanner) return 0;
    std::string value = scanner->NextToken();
    std::string token = scanner->PeekToken();
    if (token == ",") scanner->NextToken();
    return 1;
}

// MenuBorder 0.01
static int HandleMenuBorder(CFdScanner* scanner, int, int, CStatus*) {
    if (!scanner) return 0;
    std::string value = scanner->NextToken();
    std::string token = scanner->PeekToken();
    if (token == ",") scanner->NextToken();
    return 1;
}

// MenuItem "text"
static int HandleMenuItem(CFdScanner* scanner, int, int, CStatus*) {
    if (!scanner) return 0;
    std::string value = scanner->NextToken();
    std::string token = scanner->PeekToken();
    if (token == ",") scanner->NextToken();
    return 1;
}
