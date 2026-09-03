#include "FrameHashNode.h"
#include "../FDFile.h"

// Reverse engineered from Warcraft III binary

FrameHashNode::FrameHashNode()
    : m_nodeId(0),
      m_frameDef(nullptr),
      m_next(nullptr) {
}

FrameHashNode::~FrameHashNode() {
}

const char* FrameHashNode::GetName() const {
    return m_name.c_str();
}

void FrameHashNode::SetName(const char* name) {
    if (name) {
        m_name = name;
    } else {
        m_name.clear();
    }
}

int32_t FrameHashNode::GetNodeId() const {
    return m_nodeId;
}

void FrameHashNode::SetNodeId(int32_t id) {
    m_nodeId = id;
}

FrameDefNode* FrameHashNode::GetFrameDef() const {
    return m_frameDef;
}

void FrameHashNode::SetFrameDef(FrameDefNode* frameDef) {
    m_frameDef = frameDef;
}

bool FrameHashNode::IsValid() const {
    return m_frameDef != nullptr;
}

void FrameHashNode::Clear() {
    m_frameDef = nullptr;
}

FrameHashNode* FrameHashNode::GetNext() const {
    return m_next;
}

void FrameHashNode::SetNext(FrameHashNode* next) {
    m_next = next;
}
