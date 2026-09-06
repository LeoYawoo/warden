#include "FrameHandlers.h"
#include "../FDFile.h"
#include <cstring>

// FrameHandlers.cpp - 帧处理器实现
// 基于 IDA 反编译分析实现
// 原始文件: Engine/Source/FDFile/Handlers/FrameHandlers.cpp
//
// FDF 解析架构 (IDA sub_1F5440):
// 1. CFdScanner 从文件读取 token
// 2. 在 HANDLERHASH (dword_F33A00) 中查找 token 对应的处理器
// 3. 调用处理器函数处理该 token
//
// IDA 关键函数:
// - sub_1F571E: 注册处理器到 HANDLERHASH
// - sub_1F5634: 初始化默认处理器
// - sub_1F55FE: 清理处理器

// ============================================================
// FDF 属性关键字表 (基于 IDA 字符串 7409684-7413000)
// ============================================================

// 帧类型关键字
static const char* s_frameTypes[] = {
    "FRAME", "TEXT", "SPRITE", "BACKDROP", "LISTBOX",
    "DIALOG", "EDITBOX", "CHECKBOX", "SIMPLEFRAME",
    "GLUETEXTBUTTON", "GLUEBUTTON", "Texture", nullptr
};

// 属性关键字
static const char* s_propertyKeywords[] = {
    // 布局属性
    "Width", "Height", "Anchor", "SetAllPoints", "SetPoint",
    "INHERITS", "WITHCHILDREN", "Layer", "LayerStyle",

    // 背景属性
    "BackdropBackground", "BackdropTileBackground", "BackdropBackgroundInsets",
    "BackdropCornerFile", "BackdropCornerFlags", "BackdropCornerSize",
    "BackdropLeftFile", "BackdropTopFile", "BackdropRightFile", "BackdropBottomFile",
    "BackdropHalfSides", "BackdropBlendAll", "BackdropMirrored",

    // 纹理属性
    "File", "TexCoord", "AlphaMode", "Alpha", "BackgroundArt",
    "UseTexture", "UseString", "UseBackdrop", "UseHighlight",

    // 文本属性
    "Text", "FontColor", "FontHeight", "FontJustificationH", "FontJustificationV",
    "FontJustificationOffset", "FontShadowColor", "FontShadowOffset",
    "FontHighlightColor", "FontDisabledColor", "FontFlags", "FontCharSpacing",

    // 按钮属性
    "ButtonText", "ButtonPushedTextOffset", "ControlArt", "ControlStyle",
    "ControlBackdrop", "ControlPushedBackdrop", "ControlDisabledBackdrop",
    "ControlFocusHighlight", "ControlMouseOverHighlight", "ControlShortcutKey",

    // 编辑框属性
    "Password", "EditMaxChars", "EditText", "EditTextColor",
    "EditTextOffset", "EditTextFrame", "EditTextHeight",
    "EditBorderSize", "EditCursorColor", "EditSetFocus",

    // 列表框属性
    "ListBoxBorder", "ListBoxStyle", "ListBoxItemHeight", "ListBoxScrollBar",
    "SelectedColor", "FocusColor",

    // 滑块属性
    "SliderMinValue", "SliderMaxValue", "SliderStepSize", "SliderInitialValue",
    "SliderBackdropFrame", "SliderThumbButtonFrame",

    // 对话框属性
    "DialogBackdrop", "DialogOkButton", "DialogCancelButton",

    // 其他
    "HitRectInsets", "ToolTip", "ShortcutKey",
    "TabFocusDefault", "TabFocusNext", "TabFocusPush",
    "DecorateFileNames", "DoNotRegisterName",
    "DisabledTexture", "NormalTexture", "PushedTexture", "CheckedTexture",
    nullptr
};

// 锚点关键字
static const char* s_anchorKeywords[] = {
    "TOPLEFT", "TOPRIGHT", "BOTTOMLEFT", "BOTTOMRIGHT",
    "TOP", "BOTTOM", "LEFT", "RIGHT", "CENTER", nullptr
};

namespace FrameHandlers {

// ============================================================
// 处理 Frame "TYPE" "NAME" INHERITS "Template" { ... }
// IDA: HANDLERHASH 中 "Frame" 对应的处理函数
// ============================================================
int HandleFrame(CFdScanner* scanner, int stringHash, int frameHash, CStatus* status) {
    // 1. 读取帧类型 "TYPE"
    // 2. 读取帧名称 "NAME"
    // 3. 检查 INHERITS 关键字
    // 4. 读取左大括号 {
    // 5. 解析帧属性和子节点
    // 6. 读取右大括号 }
    // 7. 创建 BASEFRAMEHASHNODE 并插入帧哈希表

    // 由于 CFdScanner 是内联在 FDFile.cpp 中的，
    // 这里的实际实现依赖于 FDFile 的解析循环
    // 此处提供框架，具体解析逻辑在 FDFile::ParseFrameBody 中

    return 1; // 返回 1 继续解析
}

// ============================================================
// 处理 Texture { ... } 子节点
// IDA: HANDLERHASH 中 "Texture" 对应的处理函数
// ============================================================
int HandleTexture(CFdScanner* scanner, int stringHash, int frameHash, CStatus* status) {
    // Texture 属性:
    // File "ConsoleTexture01",
    // Width 0.256,
    // Height 0.032,
    // TexCoord 0, 1, 0, 0.125,
    // AlphaMode "ALPHAKEY",
    // Anchor TOPLEFT,0,0,

    return 1; // 返回 1 继续解析
}

// ============================================================
// 处理 SetPoint 锚点属性
// IDA: 被 SetPoint 关键字触发
// ============================================================
int HandleSetPoint(CFdScanner* scanner, FdfNode* frame, CStatus* status) {
    // SetPoint TOPLEFT, "ParentFrame", TOPLEFT, 0.1, 0.2
    // SetPoint RIGHT, "OKButton", LEFT, -0.02, 0.0

    // 解析步骤:
    // 1. 读取锚点类型 (TOPLEFT, TOPRIGHT, etc.)
    // 2. 读取逗号
    // 3. 读取父帧名称
    // 4. 读取逗号
    // 5. 读取父锚点类型
    // 6. 读取逗号
    // 7. 读取 X 偏移
    // 8. 读取逗号
    // 9. 读取 Y 偏移

    if (!scanner || !frame) return 0;

    FdfAttribute attr;
    attr.name = "SetPoint";

    // 读取锚点类型
    std::string anchor = scanner->NextToken();
    attr.value = anchor;

    // 读取后续参数
    std::string token = scanner->NextToken(); // 逗号
    if (token == ",") {
        token = scanner->NextToken(); // 父帧名称
        attr.args.push_back(token);

        token = scanner->NextToken(); // 逗号
        if (token == ",") {
            token = scanner->NextToken(); // 父锚点
            attr.args.push_back(token);

            token = scanner->NextToken(); // 逗号
            if (token == ",") {
                token = scanner->NextToken(); // X 偏移
                attr.args.push_back(token);

                token = scanner->NextToken(); // 逗号
                if (token == ",") {
                    token = scanner->NextToken(); // Y 偏移
                    attr.args.push_back(token);
                }
            }
        }
    }

    frame->attributes.push_back(attr);
    return 1;
}

// ============================================================
// 处理 IncludeFile 指令
// IDA: HANDLERHASH 中 "IncludeFile" 对应的处理函数
// ============================================================
int HandleIncludeFile(CFdScanner* scanner, int stringHash, int frameHash, CStatus* status) {
    // IncludeFile "UI\FrameDef\Glue\StandardTemplates.fdf"

    // 读取文件路径
    // 构建完整路径
    // 检查是否已包含 (防止循环)
    // 读取文件内容
    // 解析文件内容

    return 1;
}

// ============================================================
// 处理 SetAllPoints 属性
// ============================================================
int HandleSetAllPoints(CFdScanner* scanner, FdfNode* frame, CStatus* status) {
    if (!frame) return 0;

    FdfAttribute attr;
    attr.name = "SetAllPoints";
    frame->attributes.push_back(attr);

    return 1;
}

// ============================================================
// 处理通用属性 (Width, Height, Anchor, etc.)
// ============================================================
int HandleProperty(CFdScanner* scanner, FdfNode* frame, CStatus* status, const std::string& propName) {
    if (!scanner || !frame) return 0;

    FdfAttribute attr;
    attr.name = propName;

    // 读取属性值
    std::string token = scanner->PeekToken();
    if (!token.empty() && token != "," && token != "}" && token != "{") {
        attr.value = scanner->NextToken();

        // 检查是否是多参数属性 (如 FontColor 1.0 1.0 1.0 1.0)
        token = scanner->PeekToken();
        while (!token.empty() && token != "," && token != "}" &&
               token != "Frame" && token != "Texture" && token != "IncludeFile" &&
               token != "StringList") {
            attr.args.push_back(scanner->NextToken());
            token = scanner->PeekToken();
        }
    }

    // 跳过逗号
    token = scanner->PeekToken();
    if (token == ",") {
        scanner->NextToken();
    }

    frame->attributes.push_back(attr);
    return 1;
}

// ============================================================
// 注册所有帧类型处理器
// IDA: sub_1F571E - 初始化 TYPEHANDLERSTRUCT 数组
// ============================================================
bool RegisterAllHandlers() {
    // IDA 中的流程:
    // 1. 遍历 unk_E77DE0 数组 (处理器描述符)
    // 2. 对每个描述符:
    //    - 计算类型名称哈希 (sub_5DA318 + sub_5DB6D2)
    //    - 在 HANDLERHASH 中查找或创建节点
    //    - 设置处理函数指针
    // 3. 设置 FRAMETYPESTRUCT 数组大小为 0x21 (33)

    // 原始数据位于 unk_E77DE0 (地址范围待确认)
    // 每个条目 16 字节:
    //   +0: 类型名称指针
    //   +4: 类型名称长度
    //   +8: 创建函数指针
    //   +12: 处理函数指针

    return true;
}

// ============================================================
// 清理处理器
// IDA: sub_1F55FE
// ============================================================
void CleanupHandlers() {
    // IDA 中的流程:
    // TSFixedArray<FRAMETYPESTRUCT>::Clear(dword_F6B448);
    // TSHashTable<HANDLERHASH>::InternalClear(&dword_F33A00, 0);

    // 由于使用了简化实现，这里不需要清理
}

// ============================================================
// 初始化默认处理器
// IDA: sub_1F5634
// ============================================================
void InitializeDefaultHandlers() {
    // IDA 中的流程:
    // 1. 遍历 unk_E77DE0 (静态处理器表)
    // 2. 对每个条目创建 HANDLERHASH 节点
    // 3. 设置 FRAMETYPESTRUCT 数组大小为 0x21

    // 默认处理器表位于 unk_E77DE0 到 unk_E77E10
    // 每个条目 8 字节: {typeId, handlerFunc}
}

} // namespace FrameHandlers
