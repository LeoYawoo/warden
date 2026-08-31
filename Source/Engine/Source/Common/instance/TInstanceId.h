#pragma once

#include <cstdint>
#include "Common/TSLinkedNode.h"

template<class T>
class TInstanceId : public TSLinkedNode<T> {
public:
    // Member variables
    uint32_t m_id;
};


