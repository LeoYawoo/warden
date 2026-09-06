#include "FrameHashNode.h"
#include "../FDFile.h"
#include <cstring>

// FrameHashNode.cpp - 帧哈希节点实现
// 基于 IDA 反编译分析实现

FrameHashNode::FrameHashNode()
    : m_next(nullptr)
    , m_prev(nullptr)
    , m_nodeId(0)
    , m_frameDef(nullptr)
    , m_isValid(false)
    , m_isInUse(false) {
    m_name[0] = '\0';
}

FrameHashNode::~FrameHashNode() {
}

const char* FrameHashNode::GetName() const {
    return m_name;
}

void FrameHashNode::SetName(const char* name) {
    if (name) {
        strncpy(m_name, name, sizeof(m_name) - 1);
        m_name[sizeof(m_name) - 1] = '\0';
    } else {
        m_name[0] = '\0';
    }
}

int32_t FrameHashNode::GetNodeId() const {
    return m_nodeId;
}

void FrameHashNode::SetNodeId(int32_t id) {
    m_nodeId = id;
}

FdfNode* FrameHashNode::GetFrameDef() const {
    return m_frameDef;
}

void FrameHashNode::SetFrameDef(FdfNode* frameDef) {
    m_frameDef = frameDef;
    m_isValid = (frameDef != nullptr);
}

bool FrameHashNode::IsValid() const {
    return m_isValid;
}

bool FrameHashNode::IsInUse() const {
    return m_isInUse;
}

void FrameHashNode::Clear() {
    m_frameDef = nullptr;
    m_isValid = false;
    m_isInUse = false;
    m_name[0] = '\0';
}

FrameHashNode* FrameHashNode::GetNext() const {
    return m_next;
}

void FrameHashNode::SetNext(FrameHashNode* next) {
    m_next = next;
}

FrameHashNode* FrameHashNode::GetPrev() const {
    return m_prev;
}

void FrameHashNode::SetPrev(FrameHashNode* prev) {
    m_prev = prev;
}
