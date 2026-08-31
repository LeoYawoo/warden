#include "C22uMatrix.h"

using namespace Tempest;

C22uMatrix::C22uMatrix(const softfloat &a2, const softfloat &a3, const softfloat &a4, const softfloat &a5) {
    this->a0 = a2;
    this->a1 = a3;
    this->b0 = a4;
    this->b1 = a5;
}
