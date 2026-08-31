#pragma once

#include <cstdint>

template<class T>
class IDatabase {
public:
    // Member variables
    T *m_records = nullptr;
    T **m_recordsById = nullptr;

    // Virtual member functions
    virtual T *GetRecord(int32_t id) = 0;
};


