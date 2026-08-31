#include "CRect.h"
#include "C2Vector.h"
#include <cmath>

using namespace Tempest;

CRect CRect::Intersection(const CRect &l, const CRect &r) {
    CRect i;

    i.maxX = r.maxX <= l.maxX ? r.maxX : l.maxX;
    i.maxY = r.maxY <= l.maxY ? r.maxY : l.maxY;
    i.minX = r.minX >= l.minX ? r.minX : l.minX;
    i.minY = r.minY >= l.minY ? r.minY : l.minY;

    return i;
}

CRect CRect::Union(const CRect &l, const CRect &r) {
    CRect u;

    u.minX = l.minX <= r.minX ? l.minX : r.minX;
    u.minY = l.minY <= r.minY ? l.minY : r.minY;
    u.maxX = l.maxX >= r.maxX ? l.maxX : r.maxX;
    u.maxY = l.maxY >= r.maxY ? l.maxY : r.maxY;

    return u;
}

CRect::CRect() {
    minY = 0.0f;
    minX = 0.0f;
    maxY = 0.0f;
    maxX = 0.0f;
}

CRect::CRect(float miny, float minx, float maxy, float maxx) : minY(miny), minX(minx), maxY(maxy), maxX(maxx) {}

bool CRect::operator==(const CRect &rect) const {
    return this->minX == rect.minX && this->minY == rect.minY && this->maxX == rect.maxX &&
           this->maxY == rect.maxY;
}

bool CRect::operator!=(const CRect &rect) const {
    return !(*this == rect);
}

bool CRect::IsPointInside(const C2Vector &pt) const {
    return this->minX <= pt.x && this->maxX >= pt.x && this->minY <= pt.y && this->maxY >= pt.y;
}

bool CRect::Contains(const C2Vector &pt) const {
    return this->IsPointInside(pt);
}

bool CRect::Contains(const CRect &r) const {
    return this->minX <= r.minX && this->maxX >= r.maxX &&
           this->minY <= r.minY && this->maxY >= r.maxY;
}

CRect *CRect::Clamp(C2Vector &a2) {
    float y;
    float lminy;
    float lminx;

    y = a2.y;
    if (this->minY <= y)
        lminy = fminf(this->maxY, y);
    else
        lminy = this->minY;
    a2.y = lminy;
    if (this->minX <= a2.x)
        lminx = fminf(this->maxX, a2.x);
    else
        lminx = this->minX;
    a2.x = lminx;
    return this;
}

void CRect::Expand(const C2Vector &pt) {
    if (pt.x < this->minX) this->minX = pt.x;
    if (pt.x > this->maxX) this->maxX = pt.x;
    if (pt.y < this->minY) this->minY = pt.y;
    if (pt.y > this->maxY) this->maxY = pt.y;
}

void CRect::Expand(const CRect &r) {
    if (r.minX < this->minX) this->minX = r.minX;
    if (r.maxX > this->maxX) this->maxX = r.maxX;
    if (r.minY < this->minY) this->minY = r.minY;
    if (r.maxY > this->maxY) this->maxY = r.maxY;
}

C2Vector CRect::Center() const {
    return C2Vector((this->minX + this->maxX) * 0.5f, (this->minY + this->maxY) * 0.5f);
}

bool CRect::Sub4826D0() const {
    return this->maxY < 0.0f || this->minY > 1.0f || this->maxX < 0.0f || this->minX > 1.0f;
}

float CRect::Width() const {
    return this->maxX - this->minX;
}

float CRect::Height() const {
    return this->maxY - this->minY;
}