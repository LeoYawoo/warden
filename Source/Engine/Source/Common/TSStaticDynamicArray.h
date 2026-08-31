#pragma once

#include "TSBaseArray.h"
#include "../Storm/Memory.h"

template<typename T, int N>
class TSStaticDynamicArray {
public:
    TSStaticDynamicArray() : size_(0), m_capacity(0), m_data(nullptr) {}

    TSStaticDynamicArray(TSBaseArray<T> &a2) : size_(0), m_capacity(0), m_data(nullptr) {
        Set(a2.data, a2.Ptr());
    }

    ~TSStaticDynamicArray() {
        if (this->size_ > N)
            return DeallocateMemory(this->m_data);
    }

    unsigned int Add(unsigned int a2, int *a3) {
        int v4;
        unsigned int i;

        Reserve(a2, 1);
        for (i = 0; i < a2; ++i)
            sub_71D008(this->m_data + 4 * (this->m_capacity + i), a3++);
        v4 = this->m_capacity + a2;
        this->m_capacity = v4;
        return v4 - a2;
    }

    int Reserve(unsigned int a2, int a3) {
        int result;
        unsigned int v4;

        result = a3;
        v4 = a2 + this->m_capacity;
        if (v4 > this->size_) {
            if (a3 && v4 > N && (v4 & 0x3F) != 0)
                v4 += 64 - (v4 & 0x3F);
            return ReallocData(v4);
        }
        return result;
    }

    void ReallocData(unsigned int a2) {
        void *v8 = this->m_data;
        for (unsigned int i = a2; i < this->m_capacity; ++i);
        void *v4 = nullptr;
        if (a2 <= 0x200) {
            v4 = &this->field_C;
            if (v8 == &this->field_C) {
                this->size_ = a2;
                return;
            }
        } else if (this->size_ > N) {
            this->m_data = sub_B4C8(v8, 4 * a2, "nothing", -2, 16);
            if (this->m_data) {
                this->size_ = a2;
                return;
            }
            v4 = sub_B3FE(4 * a2, "nothing", -2, 0);
        } else {
            v4 = sub_B3FE(4 * a2, "nothing", -2, 0);
        }
        this->m_data = v4;
        this->size_ = a2;
        if (v8) {
            int v2 = a2;
            if (a2 >= this->m_capacity)
                v2 = this->m_capacity;
            unsigned int v9 = v2;
            unsigned int v6 = 0;
            int v7 = 0;
            while (v6 < v9) {
                sub_71D008(this->m_data + v7, (char *) v8 + v7);
                ++v6;
                v7 += 4;
            }
            if (v8 != &this->field_C)
                DeallocateMemory(v8);
        }
    }

private:
    unsigned int size_;
    unsigned int m_capacity;
    T *m_data;
};


