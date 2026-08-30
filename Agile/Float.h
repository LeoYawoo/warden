
#pragma once


#include "CAgentField.h"

class Float : public CAgentField {
public:
    Float();

    explicit Float(float value);

    ~Float();

    float GetValue() const;

    void SetValue(float value);

    Float &operator+=(Float const &rhs);

    Float &operator-=(Float const &rhs);

    Float &operator*=(float scalar);

    Float &operator/=(float scalar);

    Float operator+(Float const &rhs) const;

    Float operator-(Float const &rhs) const;

    bool operator==(Float const &rhs) const;

    bool operator!=(Float const &rhs) const;

    bool operator<(Float const &rhs) const;

    bool operator>(Float const &rhs) const;

    operator float() const;

private:
    float m_value = 0.0f;
};



