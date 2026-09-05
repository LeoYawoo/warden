#pragma once

#include <cstdint>
#include <cstring>

// Reverse engineered from Warcraft III binary
// parser handles Jass script parsing

#define MAX_LINE_LEN 1024

typedef char CHAR;
typedef uint32_t DWORD;
typedef char** PZPSTR;

class CParseXML {
public:
    CParseXML() {
        m_cCurBuffer[0] = '\0';
        m_pCurrentIndex = nullptr;
        m_dwError = 0;
    }

    DWORD Read();
    DWORD SetError(DWORD dw) { m_dwError = dw; return m_dwError; }

    CHAR *GetFirstWord(CHAR *);
    CHAR *GetValue(CHAR *);
    DWORD Start(const CHAR *szFile);

    CHAR *GetToken();
    DWORD GetError() { return m_dwError; }

private:
    CHAR m_cCurToken[MAX_LINE_LEN];
    CHAR m_cCurWord[MAX_LINE_LEN];
    CHAR m_cCurBuffer[MAX_LINE_LEN];
    CHAR *m_pCurrentIndex;
    DWORD m_dwError;
};

// TODO: Add parser functions based on IDA analysis
