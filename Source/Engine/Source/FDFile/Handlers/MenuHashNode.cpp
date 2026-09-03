#include "MenuHashNode.h"

// Reverse engineered from Warcraft III binary

MenuHashNode::MenuHashNode()
    : m_nodeId(0),
      m_enabled(true),
      m_menuId(0) {
}

MenuHashNode::~MenuHashNode() {
}

const char* MenuHashNode::GetName() const {
    return m_name.c_str();
}

void MenuHashNode::SetName(const char* name) {
    if (name) {
        m_name = name;
    } else {
        m_name.clear();
    }
}

int32_t MenuHashNode::GetNodeId() const {
    return m_nodeId;
}

void MenuHashNode::SetNodeId(int32_t id) {
    m_nodeId = id;
}

bool MenuHashNode::IsEnabled() const {
    return m_enabled;
}

void MenuHashNode::SetEnabled(bool enabled) {
    m_enabled = enabled;
}

bool MenuHashNode::IsValid() const {
    return !m_name.empty();
}

void MenuHashNode::Clear() {
    m_name.clear();
    m_menuText.clear();
}

const char* MenuHashNode::GetMenuText() const {
    return m_menuText.c_str();
}

void MenuHashNode::SetMenuText(const char* text) {
    if (text) {
        m_menuText = text;
    } else {
        m_menuText.clear();
    }
}

int32_t MenuHashNode::GetMenuId() const {
    return m_menuId;
}

void MenuHashNode::SetMenuId(int32_t id) {
    m_menuId = id;
}
