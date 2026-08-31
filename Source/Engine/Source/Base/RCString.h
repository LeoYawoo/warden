#pragma once

#include <cstdint>
#include <cstring>
#include <string>

// RCString - 引用计数字符串类
// 基于 IDA 反编译分析实现
class RCString {
public:
    // 构造函数
    RCString();
    RCString(const char* str);
    RCString(const RCString& other);
    RCString(RCString&& other) noexcept;
    ~RCString();

    // 赋值运算符
    RCString& operator=(const char* str);
    RCString& operator=(const RCString& other);
    RCString& operator=(RCString&& other) noexcept;

    // 比较运算符
    bool operator==(const char* str) const;
    bool operator==(const RCString& other) const;
    bool operator!=(const char* str) const;
    bool operator!=(const RCString& other) const;

    // 获取字符串
    const char* c_str() const { return m_str ? m_str : ""; }
    const char* GetStr() const { return m_str ? m_str : ""; }

    // 获取长度
    size_t Length() const { return m_str ? strlen(m_str) : 0; }

    // 检查是否为空
    bool IsEmpty() const { return !m_str || m_str[0] == '\0'; }

    // 清空
    void Clear();

    // 转换为 std::string
    std::string ToString() const { return m_str ? m_str : ""; }

private:
    char* m_str;
};