#pragma once

template<typename T, int N>
class TSCArray {
public:
    TSCArray() : cnt(N) {
        T **v1 = &this->data;
        for (int i = N - 2; i != -2; --i) {
            *v1 = new T();
            v1 += sizeof(T);
        }
    }

    TSCArray(TSCArray &that) : cnt(that.cnt) {
        for (unsigned int i = 0; i < that.cnt; ++i) {
            this->data[i] = that.data[i];
        }
    }

    TSCArray &operator=(const TSCArray &that) {
        if (this != &that) {
            for (unsigned int i = 0; i < that.cnt; ++i) {
                this->data[i] = &that.data[i];
            }
            this->cnt = that.cnt;
        }
        return *this;
    }

private:
    int cnt;
    T *data;
};


