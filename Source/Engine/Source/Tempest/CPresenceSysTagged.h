#pragma once

#include "CPresenceSys.h"

// Reverse engineered from Warcraft III binary
// CPresenceSysTagged is a tagged system presence

namespace Tempest {
    class CPresenceSysTagged : public CPresenceSys {
    public:
        CPresenceSysTagged();
        ~CPresenceSysTagged();

        // Get tag
        int GetTag() const;

        // Set tag
        void SetTag(int tag);

        // Check if tagged
        bool IsTagged() const;

    private:
        int m_tag;
    };
}
