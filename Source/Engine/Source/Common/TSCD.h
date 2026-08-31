#pragma once

template<typename T>
class TSCD {
public:
    void CopyConstruct(T *destination, const T *source) {
        if (destination != nullptr) {
            *destination = (source != nullptr) ? *source : T();
        }
    }

    void Construct(T *ptr) {
        if (ptr != nullptr) {
            new(ptr) T(); // 调用 T 的默认构造函数
        }
    }
};


