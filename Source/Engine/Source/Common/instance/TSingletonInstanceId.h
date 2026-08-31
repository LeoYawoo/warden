#pragma once

#include "TInstanceId.h"
#include "TInstanceIdTable.h"

template<class T, size_t offset>
class TSingletonInstanceId : public TInstanceId<T> {
public:
    // Static variables
    static TInstanceIdTable<T, offset> s_idTable;
};

template<class T, size_t offset>
TInstanceIdTable<T, offset> TSingletonInstanceId<T, offset>::s_idTable;


