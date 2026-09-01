#include "CDBDatabase.h"
#include <cstdint>

// Reverse engineered from Warcraft III binary
// Address: 0x7E50F3

CDBDatabase::CDBDatabase(void* data) : CDatabaseBase(), m_dbData(data), m_fieldData(nullptr), m_rowCount(0), m_colCount(0) {
    // Virtual table set in constructor
    if (data) {
        // Parse DB data
        auto* bytes = static_cast<unsigned char*>(data);
        m_rowCount = *reinterpret_cast<int*>(bytes);
        m_colCount = *reinterpret_cast<int*>(bytes + 4);
        m_fieldData = reinterpret_cast<DatabaseField*>(bytes + 8);

        // Fix string pointers
        char* fieldPtr = reinterpret_cast<char*>(bytes + 8);
        int totalFields = m_rowCount * m_colCount;
        auto dataAddr = reinterpret_cast<intptr_t>(data);
        for (int i = 0; i < totalFields; i++) {
            if (*fieldPtr == 'S') {
                *reinterpret_cast<int*>(fieldPtr + 4) += static_cast<int>(dataAddr);
            }
            fieldPtr += 8;
        }
    }
    SetupFieldsAndEntries();
}

CDBDatabase::~CDBDatabase() {
    // Virtual destructor
}

void CDBDatabase::SetupFieldsAndEntries() {
    CDatabaseBase::SetupFieldsAndEntries();
}
