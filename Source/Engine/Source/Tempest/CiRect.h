#pragma once

namespace Tempest {
    class CiRect {
    public:
        CiRect();

        CiRect(int miny, int minx, int maxy, int maxx);

        int Center();

    public:
        int minY;
        int minX;
        int maxY;
        int maxX;
    };
}


