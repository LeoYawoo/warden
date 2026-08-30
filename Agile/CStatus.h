#pragma once

#include <cstdarg>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>

enum STATUS_TYPE {
    STATUS_INFO = 0x0,
    STATUS_WARNING = 0x1,
    STATUS_ERROR = 0x2,
    STATUS_FATAL = 0x3,
    STATUS_NUMTYPES = 0x4,
};

class CStatus {
public:
    // Nested type for status entries
    struct STATUSENTRY {
        STATUS_TYPE type;
        char message[256];

        STATUSENTRY() : type(STATUS_INFO) {
            message[0] = '\0';
        }

        STATUSENTRY(STATUS_TYPE t, const char* msg) : type(t) {
            strncpy(message, msg, sizeof(message) - 1);
            message[sizeof(message) - 1] = '\0';
        }
    };

    // Static variables
    static CStatus s_errorList;

    // Member functions
    CStatus() = default;

    void Add(const CStatus &status);

    void Add(STATUS_TYPE severity, const char *format, ...);

    void Clear();

    bool IsEmpty() const;

    size_t GetCount() const;

    const STATUSENTRY& GetEntry(size_t index) const;

    STATUS_TYPE GetHighestSeverity() const;

private:
    std::vector<STATUSENTRY> m_entries;
};

class CWOWClientStatus : public CStatus {
public:
    void *m_logFile = nullptr;
};

CStatus &GetGlobalStatusObj();
