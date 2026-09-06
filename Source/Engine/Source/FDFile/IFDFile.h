#pragma once
// IFDFile.h - 帧节点工厂函数接口
// 基于 IDA 反编译分析实现
// 原始文件: Engine/Source/FDFile/IFDFile.cpp

#include <cstdint>

// 前向声明
struct BASEFRAMEHASHNODE;
struct STRINGHASHNODE;
class CStatus;

// ============================================================
// IFDFile - 帧节点工厂函数集合
// 每个函数创建一种特定类型的帧哈希节点
// 对应 IDA 中 IFDFile.cpp 的 33+ 个工厂函数
// ============================================================

namespace IFDFile {

// 类型枚举 (基于 IDA 反编译)
enum FrameNodeType : int32_t {
    NODE_BASE_FRAME = 0,         // BASEFRAMEHASHNODE (0x50 bytes)
    NODE_STRING = 1,             // STRINGHASHNODE (0x104 bytes)
    NODE_BUTTON_FRAME_A = 2,     // BUTTONFRAMEHASHNODE (0x190 bytes, sub_63E0DA)
    NODE_BUTTON_FRAME_B = 3,     // BUTTONFRAMEHASHNODE (0x190 bytes)
    NODE_CHECKBOX = 4,           // 复选框 (0x11C bytes, sub_643022)
    NODE_TEXT = 5,               // 文本帧 (0x110 bytes, sub_64359A)
    NODE_SLIDER = 6,             // 滑块 (0x1FC bytes, sub_641498)
    NODE_DIALOG = 7,             // 对话框 (0x194 bytes, sub_643F94)
    NODE_MENU = 8,               // 菜单 (0x1A8 bytes, sub_63F98E)
    NODE_POPUP_MENU = 9,         // 弹出菜单 (0x1B4 bytes, sub_63B0CC)
    NODE_LISTBOX = 10,           // 列表框 (0x1F4 bytes, sub_639A94)
    NODE_DROPDOWN = 11,          // 下拉列表 (0x1C8 bytes, sub_638E94)
    NODE_EDITBOX = 12,           // 编辑框 (0x118 bytes, sub_642DE0)
    NODE_MULTILINE_EDITBOX = 13, // 多行编辑框 (0x200 bytes, sub_63F23E)
    NODE_BUTTON = 14,            // 按钮 (0x1B8 bytes, sub_64233C)
    NODE_ICON_BUTTON = 15,       // 图标按钮 (0x220 bytes, sub_642A32)
    NODE_TREEVIEW = 16,          // 树形视图 (0x1D8 bytes, sub_63AB38)
    NODE_SCROLLBAR = 17,         // 滚动条 (0x138 bytes, sub_6406DE)
    NODE_PROGRESS = 18,          // 进度条 (0x138 bytes, sub_6453A8)
    NODE_SIMPLE_FRAME = 19,      // 简单帧 (0x110 bytes, sub_64203E)
    NODE_HIGHLIGHT_FRAME = 20,   // 高亮帧 (0x134 bytes, sub_6386F8)
    NODE_FRAME_BUTTON = 21,      // 框架按钮 (0x1C0 bytes, sub_6400AE)
    NODE_STATUS_BUTTON = 22,     // 状态按钮 (0x1C8 bytes, sub_63C090)
    // ... 更多类型
};

// 工厂函数声明
// 注意: 返回 void* 因为具体类型取决于帧类型
// 调用者需要转换为相应的具体类型

// 创建 BASEFRAMEHASHNODE (行号 342)
void* CreateBaseFrameHashNode();

// 创建 STRINGHASHNODE (行号 345)
void* CreateStringHashNode();

// 创建 BUTTONFRAMEHASHNODE 类型 A (行号 348, sub_63E0DA, type 2)
void* CreateButtonFrameHashNodeA();

// 创建 BUTTONFRAMEHASHNODE 类型 B (行号 351, type 3)
void* CreateButtonFrameHashNodeB();

// 创建复选框节点 (行号 354, sub_641498, type 6)
void* CreateSliderNode();

// 创建文本帧节点 (行号 357, sub_64359A, type 5)
void* CreateTextNode();

// 创建复选框/单选框节点 (行号 360, sub_643022, type 4)
void* CreateCheckboxNode();

// 创建对话框节点 (行号 363, sub_643F94, type 7)
void* CreateDialogNode();

// 创建菜单节点 (行号 366, sub_63F98E, type 8)
void* CreateMenuNode();

// 创建弹出菜单节点 (行号 369, sub_63B0CC, type 9)
void* CreatePopupMenuNode();

// 创建列表框节点 (行号 372, sub_639A94, type 10)
void* CreateListBoxNode();

// 创建下拉列表节点 (行号 375, sub_638E94, type 11)
void* CreateDropDownNode();

// 创建编辑框节点 (行号 378, sub_642DE0, type 12)
void* CreateEditBoxNode();

// 创建多行编辑框节点 (行号 381, sub_63F23E, type 13)
void* CreateMultiLineEditBoxNode();

// 创建按钮节点 (行号 384, sub_64233C, type 14)
void* CreateButtonNode();

// 创建图标按钮节点 (行号 387, sub_642A32, type 15)
void* CreateIconButtonNode();

// 创建树形视图节点 (行号 393, sub_63AB38, type 16)
void* CreateTreeViewNode();

// 创建滚动条节点 (行号 390, sub_6406DE, type 17)
void* CreateScrollBarNode();

// 创建进度条节点 (行号 396, sub_6453A8, type 18)
void* CreateProgressBarNode();

// 创建简单帧节点 (行号 399, sub_64203E, type 19)
void* CreateSimpleFrameNode();

// 创建高亮帧节点 (行号 402, sub_6386F8, type 20)
void* CreateHighlightFrameNode();

// 创建框架按钮节点 (行号 405, sub_6400AE, type 21)
void* CreateFrameButtonNode();

// 创建状态按钮节点 (行号 408, sub_63C090, type 22)
void* CreateStatusButtonNode();

} // namespace IFDFile
