#include "CGxStringBatch.h"

// TODO: Reverse engineer from IDA

CGxStringBatch::CGxStringBatch()
    : m_flags(0)
    , m_fontBatch() {
}

CGxStringBatch::~CGxStringBatch() = default;

void CGxStringBatch::AddString(CGxString * /*string*/) {
    // TODO: Reverse engineer from IDA
}

void CGxStringBatch::Clear() {
    m_fontBatch.Clear();
}

void CGxStringBatch::RenderBatch() {
    // TODO: Reverse engineer from IDA
}
