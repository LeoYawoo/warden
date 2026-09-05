#include "CGxShader.h"

// TODO: Reverse engineer from IDA

CGxShader::CGxShader()
    : m_linktofull()
    , m_linktoslot()
    , m_hashval(0)
    , m_key()
    , refCount(0)
    , target(GxSh_Vertex)
    , loaded(0)
    , int34(0)
    , m_target(GxSh_Vertex)
    , m_name()
    , m_compiled(false) {
}

CGxShader::~CGxShader() = default;

void CGxShader::Load(void *file) {
    // TODO: Reverse engineer from IDA
}
