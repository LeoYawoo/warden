#pragma once

#include <cstdint>
#include <string>

// Status - 状态类
// 基于 IDA 反编译分析实现
class Status {
public:
    // 构造函数
    Status();
    Status(int32_t code, const std::string& message);
    ~Status();

    // 获取状态码
    int32_t GetCode() const { return m_code; }

    // 设置状态码
    void SetCode(int32_t code) { m_code = code; }

    // 获取状态消息
    const std::string& GetMessage() const { return m_message; }

    // 设置状态消息
    void SetMessage(const std::string& message) { m_message = message; }

    // 检查是否成功
    bool IsSuccess() const { return m_code == 0; }

    // 检查是否有错误
    bool HasError() const { return m_code != 0; }

    // 清除状态
    void Clear() {
        m_code = 0;
        m_message.clear();
    }

    // 设置错误
    void SetError(int32_t code, const std::string& message) {
        m_code = code;
        m_message = message;
    }

private:
    int32_t m_code;
    std::string m_message;
};
