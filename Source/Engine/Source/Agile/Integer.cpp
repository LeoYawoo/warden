#include "Integer.h"

Integer::Integer() : m_value(0), m_agentId(0), m_fieldId(0) {
}

Integer::Integer(int value) : m_value(value), m_agentId(0), m_fieldId(0) {
}

Integer::~Integer() {
}

int Integer::GetValue() const {
    return m_value;
}

void Integer::SetValue(int value) {
    m_value = value;
}

void Integer::Declare(int agentId, int fieldId, int a3, int a4, int a5, int a6) {
    m_agentId = agentId;
    m_fieldId = fieldId;
}

Integer &Integer::operator+=(int value) {
    m_value += value;
    return *this;
}

Integer &Integer::operator-=(int value) {
    m_value -= value;
    return *this;
}

Integer &Integer::operator*=(int value) {
    m_value *= value;
    return *this;
}

Integer &Integer::operator/=(int value) {
    if (value != 0) {
        m_value /= value;
    }
    return *this;
}

Integer &Integer::operator++() {
    ++m_value;
    return *this;
}

Integer Integer::operator++(int) {
    Integer temp = *this;
    ++m_value;
    return temp;
}

Integer &Integer::operator--() {
    --m_value;
    return *this;
}

Integer Integer::operator--(int) {
    Integer temp = *this;
    --m_value;
    return temp;
}

Integer Integer::operator+(int value) const {
    return Integer(m_value + value);
}

Integer Integer::operator-(int value) const {
    return Integer(m_value - value);
}

bool Integer::operator==(Integer const &rhs) const {
    return m_value == rhs.m_value;
}

bool Integer::operator!=(Integer const &rhs) const {
    return m_value != rhs.m_value;
}

bool Integer::operator<(Integer const &rhs) const {
    return m_value < rhs.m_value;
}

bool Integer::operator>(Integer const &rhs) const {
    return m_value > rhs.m_value;
}

Integer::operator int() const {
    return m_value;
}
