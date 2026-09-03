#pragma once

#include <cstdint>
#include <string>

// Forward declarations
class FrameDefNode;

// Reverse engineered from Warcraft III binary
// FrameHashNode manages frame definition hash nodes

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
    FrameDefNode* GetFrameDef() const;
    void SetFrameDef(FrameDefNode* frameDef);

    // Node operations
    bool IsValid() const;
    void Clear();

    // Node hierarchy
    FrameHashNode* GetNext() const;
    void SetNext(FrameHashNode* next);

protected:
    std::string m_name;
    int32_t m_nodeId;
    FrameDefNode* m_frameDef;
    FrameHashNode* m_next;
};
