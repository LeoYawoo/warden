#pragma once

#include "C2Vector.h"

namespace NTempest {
    class CRect {
    public:
        static CRect Intersection(const CRect &l, const CRect &r);

        static CRect Union(const CRect &l, const CRect &r);

        CRect();

        CRect(float miny, float minx, float maxy, float maxx);

        bool operator==(const CRect &rect) const;

        bool operator!=(const CRect &rect) const;

        bool IsPointInside(const C2Vector &pt) const;

        bool Contains(const C2Vector &pt) const;

        bool Contains(const CRect &r) const;

        CRect *Clamp(C2Vector &a2);

        void Expand(const C2Vector &pt);

        void Expand(const CRect &r);

        C2Vector Center() const;

        bool Sub4826D0() const;

        float Width() const;

        float Height() const;

    public:
        float minY;
        float minX;
        float maxY;
        float maxX;
    };
}


