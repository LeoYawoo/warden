#include "XMLTree.h"
#include "XMLNode.h"
#include "StormMac/Memory.h"
#include <cstring>
#include <string>

// Reverse engineered from Warcraft III binary

void XMLTree_Cleanup() {
    // Cleanup global XML state
}

void XMLTree_Free(XMLTree* tree) {
    if (tree) {
        if (tree->root) {
            delete tree->root;
        }
        SMemFree(tree, __FILE__, __LINE__, 0);
    }
}

XMLNode* XMLTree_GetRoot(XMLTree* tree) {
    if (tree) {
        return tree->root;
    }
    return nullptr;
}

XMLTree* XMLTree_Load(const char* data, uint32_t length) {
    if (!data || length == 0) {
        return nullptr;
    }

    XMLTree* tree = static_cast<XMLTree*>(SMemAlloc(sizeof(XMLTree), __FILE__, __LINE__, 0));
    if (!tree) {
        return nullptr;
    }

    tree->root = new XMLNode();
    tree->leaf = tree->root;

    // Simple XML parsing (simplified implementation)
    const char* pos = data;
    const char* end = data + length;

    while (pos < end) {
        // Skip whitespace
        while (pos < end && (*pos == ' ' || *pos == '\t' || *pos == '\n' || *pos == '\r')) {
            pos++;
        }

        if (pos >= end) {
            break;
        }

        if (*pos == '<') {
            pos++; // Skip '<'

            if (pos < end && *pos == '/') {
                // End tag
                pos++;
                while (pos < end && *pos != '>') {
                    pos++;
                }
                if (pos < end) {
                    pos++; // Skip '>'
                }

                // Move up to parent
                if (tree->leaf->m_parent) {
                    tree->leaf = tree->leaf->m_parent;
                }
            } else {
                // Start tag
                const char* nameStart = pos;
                while (pos < end && *pos != ' ' && *pos != '>' && *pos != '/') {
                    pos++;
                }

                std::string name(nameStart, pos - nameStart);

                XMLNode* node = new XMLNode();
                node->Init(tree->leaf, name.c_str());
                tree->leaf = node;

                // Skip attributes (simplified)
                while (pos < end && *pos != '>' && *pos != '/') {
                    pos++;
                }

                if (pos < end && *pos == '/') {
                    // Self-closing tag
                    pos++; // Skip '/'
                    if (pos < end && *pos == '>') {
                        pos++; // Skip '>'
                    }
                    if (tree->leaf->m_parent) {
                        tree->leaf = tree->leaf->m_parent;
                    }
                } else if (pos < end && *pos == '>') {
                    pos++; // Skip '>'
                }
            }
        } else {
            // Text content
            const char* textStart = pos;
            while (pos < end && *pos != '<') {
                pos++;
            }

            if (tree->leaf) {
                uint32_t textLen = pos - textStart;
                tree->leaf->m_body = static_cast<char*>(SMemAlloc(textLen + 1, __FILE__, __LINE__, 0));
                memcpy(tree->leaf->m_body, textStart, textLen);
                tree->leaf->m_body[textLen] = '\0';
                tree->leaf->m_bodyLen = textLen;
            }
        }
    }

    return tree;
}
