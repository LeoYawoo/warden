#pragma once

#include "CDatabaseBase.h"

// Reverse engineered from Warcraft III binary
// Address: 0x7E50F3
// CDBDatabase is a database implementation using DB files

class CDBDatabase : public CDatabaseBase {
public:
    CDBDatabase(void* data);
    virtual ~CDBDatabase();

    virtual void SetupFieldsAndEntries() override;

private:
    void* m_dbData;  // offset +8
    DatabaseField* m_fieldData;  // offset +12
    int m_rowCount;  // offset +96
    int m_colCount;  // offset +100
};
