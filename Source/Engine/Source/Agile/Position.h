#pragma once


#include "CAgentField.h"
#include "../Tempest/C3Vector.h"

class Position : public CAgentField {
public:
    Position();

    Position(float x, float y, float z);

    Position(const Tempest::C3Vector &pos);

    Position(const Position &other);

    ~Position();

    Position &operator=(const Position &other);

    Tempest::C3Vector GetPosition() const;

    void SetPosition(const Tempest::C3Vector &pos);

    void SetPosition(float x, float y, float z);

    float GetX() const;

    float GetY() const;

    float GetZ() const;

    void SetX(float x);

    void SetY(float y);

    void SetZ(float z);

    bool IsFacing(const Position &target, float threshold = 0.5f) const;

    float DistanceTo(const Position &other) const;

    float DistanceTo(const Tempest::C3Vector &pos) const;

    Tempest::C3Vector DirectionTo(const Position &other) const;

    void MoveTowards(const Position &target, float speed);

    bool operator==(const Position &rhs) const;

    bool operator!=(const Position &rhs) const;

    Position operator+(const Tempest::C3Vector &offset) const;

    Position operator-(const Tempest::C3Vector &offset) const;

    static bool IsFacing(const Position &source, const Position &target, const Position &reference, float *dotProduct = nullptr);

protected:
    Tempest::C3Vector m_position;
};



