#include "IFDFile.h"
#include "Handlers/FrameHashNode.h"
#include "Handlers/MenuHashNode.h"
#include <cstdlib>
#include <cstring>

// IFDFile.cpp - 帧节点工厂函数实现
// 基于 IDA 反编译分析实现
// 原始文件: Engine/Source/FDFile/IFDFile.cpp
//
// 每个工厂函数:
// 1. 分配内存 (使用 sub_B3FE, 即 operator new with debug info)
// 2. 调用对应构造函数
// 3. 设置类型 ID
//
// IDA 中的模式:
//   v0 = sub_B3FE(size, "filename", line, 0);
//   if (v0) constructor(v0, typeId);
//   return v0;

namespace IFDFile {

// ============================================================
// 工厂函数实现
// ============================================================

// 创建 BASEFRAMEHASHNODE (行号 342)
// 大小: 0x50, 构造函数: sub_315644, 类型: 0
void* CreateBaseFrameHashNode() {
    // 分配 BASEFRAMEHASHNODE 结构
    BASEFRAMEHASHNODE* node = static_cast<BASEFRAMEHASHNODE*>(malloc(sizeof(BASEFRAMEHASHNODE)));
    if (!node) return nullptr;

    // 初始化内存
    memset(node, 0, sizeof(BASEFRAMEHASHNODE));

    // 设置类型 ID
    node->nodeId = NODE_BASE_FRAME;
    node->isValid = false;

    return node;
}

// 创建 STRINGHASHNODE (行号 345)
// 大小: 0x104, 构造函数: sub_3158EC, 类型: 1
void* CreateStringHashNode() {
    STRINGHASHNODE* node = static_cast<STRINGHASHNODE*>(malloc(sizeof(STRINGHASHNODE)));
    if (!node) return nullptr;

    memset(node, 0, sizeof(STRINGHASHNODE));
    node->nodeId = NODE_STRING;
    node->isInUse = false;

    return node;
}

// 创建 BUTTONFRAMEHASHNODE 类型 A (行号 348)
// 大小: 0x190, 构造函数: sub_63E0DA, 类型: 2
void* CreateButtonFrameHashNodeA() {
    FrameHashNode* node = new FrameHashNode();
    node->SetNodeId(NODE_BUTTON_FRAME_A);
    return node;
}

// 创建 BUTTONFRAMEHASHNODE 类型 B (行号 351)
// 大小: 0x190, 构造函数: BUTTONFRAMEHASHNODE, 类型: 3
void* CreateButtonFrameHashNodeB() {
    FrameHashNode* node = new FrameHashNode();
    node->SetNodeId(NODE_BUTTON_FRAME_B);
    return node;
}

// 创建滑块节点 (行号 354)
// 大小: 0x1FC, 构造函数: sub_641498, 类型: 6
void* CreateSliderNode() {
    FrameHashNode* node = new FrameHashNode();
    node->SetNodeId(NODE_SLIDER);
    return node;
}

// 创建文本帧节点 (行号 357)
// 大小: 0x110, 构造函数: sub_64359A, 类型: 5
void* CreateTextNode() {
    FrameHashNode* node = new FrameHashNode();
    node->SetNodeId(NODE_TEXT);
    return node;
}

// 创建复选框/单选框节点 (行号 360)
// 大小: 0x11C, 构造函数: sub_643022, 类型: 4
void* CreateCheckboxNode() {
    FrameHashNode* node = new FrameHashNode();
    node->SetNodeId(NODE_CHECKBOX);
    return node;
}

// 创建对话框节点 (行号 363)
// 大小: 0x194, 构造函数: sub_643F94, 类型: 7
void* CreateDialogNode() {
    FrameHashNode* node = new FrameHashNode();
    node->SetNodeId(NODE_DIALOG);
    return node;
}

// 创建菜单节点 (行号 366)
// 大小: 0x1A8, 构造函数: sub_63F98E, 类型: 8
void* CreateMenuNode() {
    FrameHashNode* node = new FrameHashNode();
    node->SetNodeId(NODE_MENU);
    return node;
}

// 创建弹出菜单节点 (行号 369)
// 大小: 0x1B4, 构造函数: sub_63B0CC, 类型: 9
void* CreatePopupMenuNode() {
    MenuHashNode* node = new MenuHashNode();
    node->SetNodeId(NODE_POPUP_MENU);
    return node;
}

// 创建列表框节点 (行号 372)
// 大小: 0x1F4, 构造函数: sub_639A94, 类型: 10
void* CreateListBoxNode() {
    FrameHashNode* node = new FrameHashNode();
    node->SetNodeId(NODE_LISTBOX);
    return node;
}

// 创建下拉列表节点 (行号 375)
// 大小: 0x1C8, 构造函数: sub_638E94, 类型: 11
void* CreateDropDownNode() {
    FrameHashNode* node = new FrameHashNode();
    node->SetNodeId(NODE_DROPDOWN);
    return node;
}

// 创建编辑框节点 (行号 378)
// 大小: 0x118, 构造函数: sub_642DE0, 类型: 12
void* CreateEditBoxNode() {
    FrameHashNode* node = new FrameHashNode();
    node->SetNodeId(NODE_EDITBOX);
    return node;
}

// 创建多行编辑框节点 (行号 381)
// 大小: 0x200, 构造函数: sub_63F23E, 类型: 13
void* CreateMultiLineEditBoxNode() {
    FrameHashNode* node = new FrameHashNode();
    node->SetNodeId(NODE_MULTILINE_EDITBOX);
    return node;
}

// 创建按钮节点 (行号 384)
// 大小: 0x1B8, 构造函数: sub_64233C, 类型: 14
void* CreateButtonNode() {
    FrameHashNode* node = new FrameHashNode();
    node->SetNodeId(NODE_BUTTON);
    return node;
}

// 创建图标按钮节点 (行号 387)
// 大小: 0x220, 构造函数: sub_642A32, 类型: 15
void* CreateIconButtonNode() {
    FrameHashNode* node = new FrameHashNode();
    node->SetNodeId(NODE_ICON_BUTTON);
    return node;
}

// 创建树形视图节点 (行号 393)
// 大小: 0x1D8, 构造函数: sub_63AB38, 类型: 16
void* CreateTreeViewNode() {
    FrameHashNode* node = new FrameHashNode();
    node->SetNodeId(NODE_TREEVIEW);
    return node;
}

// 创建滚动条节点 (行号 390)
// 大小: 0x138, 构造函数: sub_6406DE, 类型: 17
void* CreateScrollBarNode() {
    FrameHashNode* node = new FrameHashNode();
    node->SetNodeId(NODE_SCROLLBAR);
    return node;
}

// 创建进度条节点 (行号 396)
// 大小: 0x138, 构造函数: sub_6453A8, 类型: 18
void* CreateProgressBarNode() {
    FrameHashNode* node = new FrameHashNode();
    node->SetNodeId(NODE_PROGRESS);
    return node;
}

// 创建简单帧节点 (行号 399)
// 大小: 0x110, 构造函数: sub_64203E, 类型: 19
void* CreateSimpleFrameNode() {
    FrameHashNode* node = new FrameHashNode();
    node->SetNodeId(NODE_SIMPLE_FRAME);
    return node;
}

// 创建高亮帧节点 (行号 402)
// 大小: 0x134, 构造函数: sub_6386F8, 类型: 20
void* CreateHighlightFrameNode() {
    FrameHashNode* node = new FrameHashNode();
    node->SetNodeId(NODE_HIGHLIGHT_FRAME);
    return node;
}

// 创建框架按钮节点 (行号 405)
// 大小: 0x1C0, 构造函数: sub_6400AE, 类型: 21
void* CreateFrameButtonNode() {
    FrameHashNode* node = new FrameHashNode();
    node->SetNodeId(NODE_FRAME_BUTTON);
    return node;
}

// 创建状态按钮节点 (行号 408)
// 大小: 0x1C8, 构造函数: sub_63C090, 类型: 22
void* CreateStatusButtonNode() {
    FrameHashNode* node = new FrameHashNode();
    node->SetNodeId(NODE_STATUS_BUTTON);
    return node;
}

} // namespace IFDFile
