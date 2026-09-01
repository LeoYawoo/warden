#pragma once

#include "Common/TRefCnt.h"

// Reverse engineered from Warcraft III binary
// Address: 0x7E4C4D
// CDatabaseBase is the base class for database operations

// Database field structure
struct DatabaseField {
    char type;
    int offset;
    char name[64];
};

// Database entry structure
struct DatabaseEntry {
    int index;
    void* data;
};

class CDatabaseBase {
public:
    CDatabaseBase();
    virtual ~CDatabaseBase();

    virtual void SetupFieldsAndEntries();

    int LocateField(const char* name);
    int LocateField(int index);
    int LocateEntry(const char* name);
    int LocateEntry(int index);

    void IncFieldAndEntryRefs();
    void DecFieldAndEntryRefs();

    int Checksum();

    int CellUnreal(int row, int col);

protected:
    // Virtual table pointer
    void* m_data;  // offset +4
    DatabaseField* m_fields;  // offset +8
    int m_fieldCount;  // offset +12
    // Hash tables simplified as pointers
    void* m_fieldHash;  // offset +16
    void* m_entryHash;  // offset +56
};
