#include "CBLPFile.h"
#include "StormMac/String.h"
#include <cstring>

// TODO: Reverse engineer from IDA

HASHKEY_TEXTUREFILE &HASHKEY_TEXTUREFILE::operator=(const char *str) {
    m_str = const_cast<char *>(str);
    return *this;
}

bool HASHKEY_TEXTUREFILE::operator==(const char *str) {
    if (!m_str || !str) {
        return m_str == str;
    }
    return strcmp(m_str, str) == 0;
}

bool HASHKEY_TEXTUREFILE::operator==(const HASHKEY_TEXTUREFILE &other) const {
    return (texFlags & 0x3F) == (other.texFlags & 0x3F) && SStrCmpI(m_str, other.m_str, 260) == 0;
}

// CBLPFile constructor/destructor are defined in Source/Engine/Source/BLPFile/blp.cpp

void CBLPFile::Close() {
    // TODO: Reverse engineer from IDA
    m_data = nullptr;
}

int32_t CBLPFile::LoadFromBuffer(void * /*buf*/) {
    // TODO: Reverse engineer from IDA
    return 0;
}

int32_t CBLPFile::LockChain2(char * /*filename*/, PIXEL_FORMAT /*format*/, MipBits * /*mipBits*/, int32_t /*bestMip*/, int32_t /*maxAnisotropy*/) {
    // TODO: Reverse engineer from IDA
    return 0;
}

uint32_t CBLPFile::GetWidth() const {
    return m_width;
}

uint32_t CBLPFile::GetHeight() const {
    return m_height;
}

uint32_t CBLPFile::GetMipCount() const {
    return m_mipCount;
}

uint32_t CBLPFile::GetAlphaBits() const {
    return m_alphaBits;
}

int32_t CBLPFile::DecodeMip(uint32_t /*mipLevel*/, void * /*dst*/, uint32_t /*dstSize*/, uint32_t * /*outWidth*/, uint32_t * /*outHeight*/) {
    // TODO: Reverse engineer from IDA
    return 0;
}
