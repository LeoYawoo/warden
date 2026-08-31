#include "CiRect.h"

using namespace Tempest;

CiRect::CiRect() : minX(0), minY(0), maxX(0), maxY(0) {}

CiRect::CiRect(int miny, int minx, int maxy, int maxx) : minX(minx), minY(miny), maxX(maxx), maxY(maxy) {}

int CiRect::Center() {
    return (this->maxX + this->minX) / 2;
}
