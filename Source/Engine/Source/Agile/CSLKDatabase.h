#pragma once

#include "CDatabaseBase.h"

// Forward declarations
class SLK;

// Reverse engineered from Warcraft III binary
// Address: 0x7E5064
// CSLKDatabase is a database implementation using SLK files

class CSLKDatabase : public CDatabaseBase {
public:
    CSLKDatabase(char* data);
    virtual ~CSLKDatabase();

    virtual void SetupFieldsAndEntries() override;

private:
    SLK* m_slkData;  // offset +96
    char* m_rawData;  // offset +8
};
