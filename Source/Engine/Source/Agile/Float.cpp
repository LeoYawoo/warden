#include "Float.h"

Float::Float() : m_value(0.0f) {
}

Float::Float(float value) : m_value(value) {
}

Float::~Float() {
}

float Float::GetValue() const {
    return m_value;
}

void Float::SetValue(float value) {
    m_value = value;
}

Float &Float::operator+=(Float const &rhs) {
    m_value += rhs.m_value;
    return *this;
}

Float &Float::operator-=(Float const &rhs) {
    m_value -= rhs.m_value;
    return *this;
}

Float &Float::operator*=(float scalar) {
    m_value *= scalar;
    return *this;
}

Float &Float::operator/=(float scalar) {
    if (scalar != 0.0f) {
        m_value /= scalar;
    }
    return *this;
}

Float Float::operator+(Float const &rhs) const {
    return Float(m_value + rhs.m_value);
}

Float Float::operator-(Float const &rhs) const {
    return Float(m_value - rhs.m_value);
}

bool Float::operator==(Float const &rhs) const {
    return m_value == rhs.m_value;
}

bool Float::operator!=(Float const &rhs) const {
    return m_value != rhs.m_value;
}

bool Float::operator<(Float const &rhs) const {
    return m_value < rhs.m_value;
}

bool Float::operator>(Float const &rhs) const {
    return m_value > rhs.m_value;
}

Float::operator float() const {
    return m_value;
}