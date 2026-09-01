#include "XMLNode.h"
#include "StormMac/Memory.h"
#include <cstring>

// Reverse engineered from Warcraft III binary

XMLNode::XMLNode()
    : m_userData(nullptr),
      m_parent(nullptr),
      m_child(nullptr),
      m_body(nullptr),
      m_bodyLen(0),
      m_offset(0),
      m_next(nullptr) {
}

XMLNode::~XMLNode() {
    // Don't delete children here to avoid circular references
    // Children should be managed separately

    // Clean up body
    if (m_body) {
        SMemFree(m_body, __FILE__, __LINE__, 0);
        m_body = nullptr;
    }
}

const char* XMLNode::GetAttributeByName(const char* name) {
    for (uint32_t i = 0; i < m_attributes.Count(); i++) {
        if (m_attributes[i].m_name.GetString() && strcmp(m_attributes[i].m_name.GetString(), name) == 0) {
            return m_attributes[i].m_value.GetString();
        }
    }
    return nullptr;
}

const char* XMLNode::GetBody() const {
    return m_body;
}

XMLNode* XMLNode::GetChildByName(const char* name) {
    XMLNode* child = m_child;
    while (child) {
        if (child->m_name.GetString() && strcmp(child->m_name.GetString(), name) == 0) {
            return child;
        }
        child = child->m_next;
    }
    return nullptr;
}

const char* XMLNode::GetName() {
    return m_name.GetString();
}

void XMLNode::Init(XMLNode* parent, const char* name) {
    m_parent = parent;
    m_name.Copy(name);

    if (parent) {
        m_next = parent->m_child;
        parent->m_child = this;
    }
}

void XMLNode::SetAttribute(const char* name, const char* value) {
    // Check if attribute already exists
    for (uint32_t i = 0; i < m_attributes.Count(); i++) {
        if (m_attributes[i].m_name.GetString() && strcmp(m_attributes[i].m_name.GetString(), name) == 0) {
            m_attributes[i].m_value.Copy(value);
            return;
        }
    }

    // Add new attribute
    XMLAttribute attr;
    attr.m_name.Copy(name);
    attr.m_value.Copy(value);

    uint32_t newCount = m_attributes.Count() + 1;
    m_attributes.SetCount(newCount);
    m_attributes[newCount - 1] = attr;
}
