#include <cstdarg>
#include <cstdio>
#include <cstring>
#include "CStatus.h"

CStatus CStatus::s_errorList;

void CStatus::Add(const CStatus &status) {
    for (size_t i = 0; i < status.GetCount(); ++i) {
        m_entries.push_back(status.GetEntry(i));
    }
}

void CStatus::Add(STATUS_TYPE severity, const char *format, ...) {
    STATUSENTRY entry;
    entry.type = severity;

    va_list args;
    va_start(args, format);
    vsnprintf(entry.message, sizeof(entry.message), format, args);
    va_end(args);

    m_entries.push_back(entry);

    // Debug output for errors and fatal
    if (severity >= STATUS_ERROR) {
        fprintf(stderr, "[STATUS %d] %s\n", severity, entry.message);
    }
}

void CStatus::Clear() {
    m_entries.clear();
}

bool CStatus::IsEmpty() const {
    return m_entries.empty();
}

size_t CStatus::GetCount() const {
    return m_entries.size();
}

const CStatus::STATUSENTRY& CStatus::GetEntry(size_t index) const {
    return m_entries[index];
}

STATUS_TYPE CStatus::GetHighestSeverity() const {
    STATUS_TYPE highest = STATUS_INFO;
    for (const auto& entry : m_entries) {
        if (entry.type > highest) {
            highest = entry.type;
        }
    }
    return highest;
}

CStatus &GetGlobalStatusObj() {
    return CStatus::s_errorList;
}