#include "Param.h"
#include <cstdlib>
#include <cstring>
#include <algorithm>

// Reverse engineered from Warcraft III binary

Param::Param() {
}

Param::~Param() {
    Clear();
}

void Param::Add(const char* name, const char* value) {
    if (name && value) {
        ParamEntry entry;
        entry.name = name;
        entry.value = value;
        m_params.push_back(entry);
    }
}

const char* Param::Get(const char* name) const {
    if (!name) {
        return nullptr;
    }

    for (const auto& param : m_params) {
        if (param.name == name) {
            return param.value.c_str();
        }
    }
    return nullptr;
}

int Param::GetInt(const char* name, int defaultValue) const {
    const char* value = Get(name);
    if (value) {
        return atoi(value);
    }
    return defaultValue;
}

float Param::GetFloat(const char* name, float defaultValue) const {
    const char* value = Get(name);
    if (value) {
        return static_cast<float>(atof(value));
    }
    return defaultValue;
}

bool Param::Has(const char* name) const {
    return Get(name) != nullptr;
}

void Param::Remove(const char* name) {
    if (!name) {
        return;
    }

    m_params.erase(
        std::remove_if(m_params.begin(), m_params.end(),
            [name](const ParamEntry& p) { return p.name == name; }),
        m_params.end()
    );
}

size_t Param::GetCount() const {
    return m_params.size();
}

void Param::Clear() {
    m_params.clear();
}

void Param::ParseCommandLine(const char* commandLine) {
    if (!commandLine) {
        return;
    }

    std::string cmd(commandLine);
    size_t pos = 0;

    while (pos < cmd.size()) {
        // Skip whitespace
        while (pos < cmd.size() && (cmd[pos] == ' ' || cmd[pos] == '\t')) {
            pos++;
        }

        if (pos >= cmd.size()) {
            break;
        }

        // Parse name
        size_t nameStart = pos;
        while (pos < cmd.size() && cmd[pos] != '=' && cmd[pos] != ' ') {
            pos++;
        }

        std::string name = cmd.substr(nameStart, pos - nameStart);

        // Parse value
        std::string value;
        if (pos < cmd.size() && cmd[pos] == '=') {
            pos++; // skip '='
            if (pos < cmd.size() && cmd[pos] == '"') {
                // Quoted value
                pos++; // skip opening quote
                size_t valueStart = pos;
                while (pos < cmd.size() && cmd[pos] != '"') {
                    pos++;
                }
                value = cmd.substr(valueStart, pos - valueStart);
                if (pos < cmd.size()) {
                    pos++; // skip closing quote
                }
            } else {
                // Unquoted value
                size_t valueStart = pos;
                while (pos < cmd.size() && cmd[pos] != ' ') {
                    pos++;
                }
                value = cmd.substr(valueStart, pos - valueStart);
            }
        }

        if (!name.empty()) {
            Add(name.c_str(), value.c_str());
        }
    }
}

void Param::ParseString(const char* str) {
    ParseCommandLine(str);
}
