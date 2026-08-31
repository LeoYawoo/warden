#pragma once

#include <cstdint>
#include <cstring>
#include <vector>

// MsgBuffer - 消息缓冲区类
// 基于 IDA 反编译分析实现
class MsgBuffer {
public:
    // 构造函数
    MsgBuffer();
    MsgBuffer(uint32_t initialSize);
    ~MsgBuffer();

    // 获取数据指针
    const uint8_t* GetData() const { return m_data.data(); }

    // 获取数据大小
    uint32_t GetSize() const { return m_size; }

    // 获取容量
    uint32_t GetCapacity() const { return m_capacity; }

    // 检查是否为空
    bool IsEmpty() const { return m_size == 0; }

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

    // 清空缓冲区
    void Clear();

    // 重置缓冲区
    void Reset();

    // 获取剩余可读字节数
    uint32_t Remaining() const { return m_size - m_position; }

    // 检查是否可以读取指定字节数
    bool CanRead(uint32_t bytes) const { return m_position + bytes <= m_size; }

    // 获取数据存储状态
    int32_t GetState() const { return m_state; }

    // 设置数据存储状态
    void SetState(int32_t state) { m_state = state; }

private:
    std::vector<uint8_t> m_data;
    uint32_t m_size;
    uint32_t m_capacity;
    uint32_t m_position;
    int32_t m_state;
};
