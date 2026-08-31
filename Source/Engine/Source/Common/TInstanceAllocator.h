#pragma once

template<typename T>
class TInstanceAllocator {
public:
    TInstanceAllocator(unsigned long elementCount) {
        construct(sizeof(T), elementCount);
    }

    int Get(int index) {
        int v2 = get(index, "", -2);
        if (v2)
            sub_B22F4(v2);
        return v2;
    }

    int Put(T *target) {
        sub_B264C(target);
        return sub_B94A(this, target);
    }

private:
    void construct(unsigned int elementSize, int elementCount) {
        this->m_elementSize = (elementSize > 3) ? elementSize : 4; // 元素大小根据条件设置
        this->m_elementCount = (elementCount == 0) ? 1 : elementCount; // 元素总数根据条件设置
        this->m_allocatedCount = 0; // 已分配元素数量初始化为0
        this->m_maxAllocatedCount = 0; // 最大已分配元素数量初始化为0
        this->m_unused = 0; // 未使用的初始化为0
    }

    size_t get(int elementCount, const char *filePath, int line) {
        size_t elementSize = this->m_elementSize;
        if (elementSize == 1) {
            filePath = nullptr;
            line = 0;
        }
        if (!this->m_unused) {
            if (!filePath) {
                filePath = "/Volumes/F1/usrbuild/xb/build/War3x_B6401/War3/Source/Mac/../../../Engine/Source/Base/CDataAllocator.cpp";
                line = 152;
            }
            void *allocatedMemory = (void *) sub_B3FE(this->m_elementSize * elementSize + 4, filePath, line, 0);
            void *current = allocatedMemory + 1;
            this->m_unused = (size_t)(allocatedMemory + 1);
            for (unsigned int i = 0; i < this->m_elementSize - 1; ++i) {
                void *next = (void *) ((char *) current + elementSize);
                *current = next;
                current = next;
            }
            *current = 0;
            *allocatedMemory = this->m_maxAllocatedCount;
            this->m_maxAllocatedCount = (size_t) allocatedMemory;
        }
        size_t result = this->m_unused;
        this->m_unused = result;
        if (elementCount && (int) this->m_elementSize > 0)
            memset(result, 0, this->m_elementSize);
        ++this->m_allocatedCount;
        return result;
    }
    int sub_B22F4()
    {
        int result;

        this->m_unused = 0;
        this->m_wordValue = 0;
        this->m_elementSize = 4;
        result = TPow2TableAllocator<TSLiteList<ObserverEventReg>, 4, 64>::GetTable(dword_F31040, 0);
        this->m_allocatedCount = result;
        return result;
    }
private:
    unsigned int m_elementSize;
    int m_elementCount;
    int m_allocatedCount;
    int m_maxAllocatedCount;
    int m_unused;

};



