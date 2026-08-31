#pragma once

#include <cstdint>
#include <cstring>
#include <vector>

// CDataStore - 数据存储类
// 基于 IDA 反编译分析实现
class CDataStore {
public:
    // 构造函数
    CDataStore();
    virtual ~CDataStore();

    // 重置数据存储
    void Reset();

    // 销毁数据存储
    void Destroy();

    // 获取数据指针
    const uint8_t* GetData() const { return m_data; }

    // 获取数据大小
    uint32_t GetSize() const { return m_usedSize; }

    // 获取已使用大小
    uint32_t GetUsedSize() const { return m_usedSize; }

    // 获取容量
    uint32_t GetCapacity() const { return m_capacity; }

    // 检查是否为空
    bool IsEmpty() const { return m_usedSize == 0; }

    // 检查是否已满
    bool IsFull() const { return m_usedSize >= m_capacity; }

    // 写入数据
    bool Write(const void* data, uint32_t size);

    // 读取数据
    bool Read(void* buffer, uint32_t size);

    // 跳过指定字节
    bool Skip(uint32_t bytes);

    // 获取当前位置
    uint32_t Tell() const { return m_position; }

    // 设置位置
    bool Seek(uint32_t position);

    // 获取剩余可读字节数
    uint32_t Remaining() const { return m_usedSize - m_position; }

    // 检查是否可以读取指定字节数
    bool CanRead(uint32_t bytes) const { return m_position + bytes <= m_usedSize; }

    // 检查是否可以写入指定字节数
    bool CanWrite(uint32_t bytes) const { return m_usedSize + bytes <= m_capacity; }

    // 获取数据存储状态
    int32_t GetState() const { return m_state; }

    // 设置数据存储状态
    void SetState(int32_t state) { m_state = state; }

private:
    // 虚函数表指针（IDB 中的 offset 0）
    void** m_vtable;

    // 内部数据指针（IDB 中的 offset 4）
    uint8_t* m_data;

    // 内部数据大小（IDB 中的 offset 8）
    uint32_t m_dataSize;

    // 已使用大小（IDB 中的 offset 12）
    uint32_t m_usedSize;

    // 容量（IDB 中的 offset 16）
    uint32_t m_capacity;

    // 当前位置（IDB 中的 offset 20）
    uint32_t m_position;

    // 状态（IDB 中的 offset 24）
    int32_t m_state;
};
