#pragma once

#include <cstdint>
#include <string>

// Reverse engineered from Warcraft III binary
// MenuHashNode manages menu definition hash nodes

class MenuHashNode {
public:
    MenuHashNode();
    ~MenuHashNode();

    // Node properties
    const char* GetName() const;
    void SetName(const char* name);

    int32_t GetNodeId() const;
    void SetNodeId(int32_t id);

    // Node state
    bool IsEnabled() const;
    void SetEnabled(bool enabled);

    // Node operations
    bool IsValid() const;
    void Clear();

    // Menu specific
    const char* GetMenuText() const;
    void SetMenuText(const char* text);

    int32_t GetMenuId() const;
    void SetMenuId(int32_t id);

protected:
    std::string m_name;
    int32_t m_nodeId;
    bool m_enabled;
    std::string m_menuText;
    int32_t m_menuId;
};
