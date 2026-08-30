#pragma once


#include "CAgentField.h"

class Integer : public CAgentField {
public:
    Integer();

    explicit Integer(int value);

    ~Integer();

    int GetValue() const;

    void SetValue(int value);

    void Declare(int agentId, int fieldId, int a3, int a4, int a5, int a6);

    Integer &operator+=(int value);

    Integer &operator-=(int value);

    Integer &operator*=(int value);

    Integer &operator/=(int value);

    Integer &operator++();

    Integer operator++(int);

    Integer &operator--();

    Integer operator--(int);

    Integer operator+(int value) const;

    Integer operator-(int value) const;

    bool operator==(Integer const &rhs) const;

    bool operator!=(Integer const &rhs) const;

    bool operator<(Integer const &rhs) const;

    bool operator>(Integer const &rhs) const;

    operator int() const;

private:
    int m_value = 0;
    int m_agentId = 0;
    int m_fieldId = 0;
};



