#include "CGxString.h"

// TODO: Reverse engineer from IDA

CGxString::CGxString()
    : m_flags(0) {
}

CGxString::~CGxString() = default;

CGxString *CGxString::GetNewString(int32_t /*a1*/) {
    // TODO: Reverse engineer from IDA
    return nullptr;
}

int32_t CGxString::Initialize(float /*fontHeight*/, const Tempest::C3Vector & /*position*/,
                              float /*blockWidth*/, float /*blockHeight*/, CGxFont * /*font*/, const char * /*text*/,
                              EGxFontVJusts /*vJust*/, EGxFontHJusts /*hJust*/, float /*spacing*/,
                              uint32_t /*flags*/, const Tempest::CImVector & /*color*/, float /*scale*/) {
    // TODO: Reverse engineer from IDA
    return 0;
}

void CGxString::AddShadow(Tempest::C2Vector /*offset*/, const Tempest::CImVector & /*color*/) {
    // TODO: Reverse engineer from IDA
}

void CGxString::SetColor(const Tempest::CImVector & /*color*/) {
    // TODO: Reverse engineer from IDA
}

void CGxString::SetStringPosition(const Tempest::C3Vector & /*position*/) {
    // TODO: Reverse engineer from IDA
}

void CGxString::Tick() {
    // TODO: Reverse engineer from IDA
}

void CGxString::Recycle() {
    // TODO: Reverse engineer from IDA
}
