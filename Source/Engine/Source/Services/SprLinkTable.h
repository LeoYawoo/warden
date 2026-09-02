#pragma once

#include <cstdint>
#include <vector>

// Reverse engineered from Warcraft III binary
// SprLinkTable manages sprite link tables

class SprLinkTable {
public:
    SprLinkTable();
    ~SprLinkTable();

    // Link table operations
    void AddLink(int32_t fromId, int32_t toId);
    void RemoveLink(int32_t fromId, int32_t toId);

    // Link queries
    bool HasLink(int32_t fromId, int32_t toId) const;
    std::vector<int32_t> GetLinks(int32_t fromId) const;
    size_t GetLinkCount() const;

    // Table operations
    void Clear();
    bool IsEmpty() const;

protected:
    struct Link {
        int32_t fromId;
        int32_t toId;
    };

    std::vector<Link> m_links;
};
