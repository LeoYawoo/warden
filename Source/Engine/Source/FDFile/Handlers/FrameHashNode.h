#pragma once

#include <cstdint>
#include <string>

// Forward declarations
struct FdfNode;

// FrameHashNode - 帧哈希节点
// 基于 IDA 反编译分析实现
// 对应 IDA 中的 BASEFRAMEHASHNODE 结构
//
// IDA 结构布局:
// offset 0:  next (TSLink 指针)
// offset 4:  prev (TSLink 指针)
// offset 8:  nodeId (类型 ID)
// offset 12: name[260] (帧名称)
// offset 272: frameDef (FdfNode*)
// offset 276: isValid
// offset 280: isInUse (IDA offset 48 检查)

class FrameHashNode {
public:
    FrameHashNode();
    ~FrameHashNode();

    // Node properties
    const char* GetName() const;
    void SetName(const char* name);

    int32_t GetNodeId() const;
    void SetNodeId(int32_t id);

    // Node data
    FdfNode* GetFrameDef() const;
    void SetFrameDef(FdfNode* frameDef);

    // Node operations
    bool IsValid() const;
    bool IsInUse() const;
    void Clear();

    // Node hierarchy (TSLink 接口)
    FrameHashNode* GetNext() const;
    void SetNext(FrameHashNode* next);
    FrameHashNode* GetPrev() const;
    void SetPrev(FrameHashNode* prev);

protected:
    // TSLink 指针
    FrameHashNode* m_next;
    FrameHashNode* m_prev;

    // 节点信息
    int32_t m_nodeId;
    char m_name[260];           // 帧名称 (MAX_PATH)
    FdfNode* m_frameDef;        // 帧定义节点
    bool m_isValid;
    bool m_isInUse;             // IDA offset 48 检查
};
