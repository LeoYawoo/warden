#include "Position.h"
#include <cmath>

Position::Position() : m_position(0.0f, 0.0f, 0.0f) {
}

Position::Position(float x, float y, float z) : m_position(x, y, z) {
}

Position::Position(const Tempest::C3Vector &pos) : m_position(pos) {
}

Position::Position(const Position &other) : m_position(other.m_position) {
}

Position::~Position() {
}

Position &Position::operator=(const Position &other) {
    if (this != &other) {
        m_position = other.m_position;
    }
    return *this;
}

Tempest::C3Vector Position::GetPosition() const {
    return m_position;
}

void Position::SetPosition(const Tempest::C3Vector &pos) {
    m_position = pos;
}

void Position::SetPosition(float x, float y, float z) {
    m_position.x = x;
    m_position.y = y;
    m_position.z = z;
}

float Position::GetX() const {
    return m_position.x;
}

float Position::GetY() const {
    return m_position.y;
}

float Position::GetZ() const {
    return m_position.z;
}

void Position::SetX(float x) {
    m_position.x = x;
}

void Position::SetY(float y) {
    m_position.y = y;
}

void Position::SetZ(float z) {
    m_position.z = z;
}

bool Position::IsFacing(const Position &target, float threshold) const {
    Tempest::C3Vector dir = DirectionTo(target);
    dir.Normalize();
    return dir.z >= threshold;
}

float Position::DistanceTo(const Position &other) const {
    return DistanceTo(other.m_position);
}

float Position::DistanceTo(const Tempest::C3Vector &pos) const {
    float dx = m_position.x - pos.x;
    float dy = m_position.y - pos.y;
    float dz = m_position.z - pos.z;
    return std::sqrt(dx * dx + dy * dy + dz * dz);
}

Tempest::C3Vector Position::DirectionTo(const Position &other) const {
    return Tempest::C3Vector(
        other.m_position.x - m_position.x,
        other.m_position.y - m_position.y,
        other.m_position.z - m_position.z
    );
}

void Position::MoveTowards(const Position &target, float speed) {
    Tempest::C3Vector dir = DirectionTo(target);
    float dist = dir.Mag();
    if (dist > 0.0f && dist > speed) {
        dir.Normalize();
        m_position.x += dir.x * speed;
        m_position.y += dir.y * speed;
        m_position.z += dir.z * speed;
    } else if (dist > 0.0f) {
        m_position = target.m_position;
    }
}

bool Position::operator==(const Position &rhs) const {
    return m_position == rhs.m_position;
}

bool Position::operator!=(const Position &rhs) const {
    return m_position != rhs.m_position;
}

Position Position::operator+(const Tempest::C3Vector &offset) const {
    return Position(m_position + offset);
}

Position Position::operator-(const Tempest::C3Vector &offset) const {
    return Position(m_position - offset);
}

bool Position::IsFacing(const Position &source, const Position &target, const Position &reference, float *dotProduct) {
    Tempest::C3Vector dirToTarget = target.DirectionTo(source);
    Tempest::C3Vector dirToRef = reference.DirectionTo(source);
    dirToTarget.Normalize();
    dirToRef.Normalize();
    float dot = dirToTarget.Dot(dirToRef);
    if (dotProduct) {
        *dotProduct = dot;
    }
    return dot >= 0.0f;
}
