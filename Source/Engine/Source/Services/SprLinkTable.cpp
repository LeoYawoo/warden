#include "SprLinkTable.h"
#include <algorithm>

// Reverse engineered from Warcraft III binary

SprLinkTable::SprLinkTable() {}
SprLinkTable::~SprLinkTable() { Clear(); }

void SprLinkTable::AddLink(int32_t fromId, int32_t toId) {
    m_links.push_back({fromId, toId});
}

void SprLinkTable::RemoveLink(int32_t fromId, int32_t toId) {
    m_links.erase(
        std::remove_if(m_links.begin(), m_links.end(),
            [fromId, toId](const Link& l) { return l.fromId == fromId && l.toId == toId; }),
        m_links.end());
}

bool SprLinkTable::HasLink(int32_t fromId, int32_t toId) const {
    return std::any_of(m_links.begin(), m_links.end(),
        [fromId, toId](const Link& l) { return l.fromId == fromId && l.toId == toId; });
}

std::vector<int32_t> SprLinkTable::GetLinks(int32_t fromId) const {
    std::vector<int32_t> result;
    for (const auto& link : m_links) {
        if (link.fromId == fromId) {
            result.push_back(link.toId);
        }
    }
    return result;
}

size_t SprLinkTable::GetLinkCount() const {
    return m_links.size();
}

void SprLinkTable::Clear() {
    m_links.clear();
}

bool SprLinkTable::IsEmpty() const {
    return m_links.empty();
}
