#pragma once

#include <cstdint>
#include <string>
#include <vector>

// Reverse engineered from Warcraft III binary
// Param manages parameter parsing and storage

class Param {
public:
    Param();
    ~Param();

    // Add parameter
    void Add(const char* name, const char* value);

    // Get parameter value
    const char* Get(const char* name) const;

    // Get parameter value as int
    int GetInt(const char* name, int defaultValue = 0) const;

    // Get parameter value as float
    float GetFloat(const char* name, float defaultValue = 0.0f) const;

    // Check if parameter exists
    bool Has(const char* name) const;

    // Remove parameter
    void Remove(const char* name);

    // Get parameter count
    size_t GetCount() const;

    // Clear all parameters
    void Clear();

    // Parse command line
    void ParseCommandLine(const char* commandLine);

    // Parse string
    void ParseString(const char* str);

private:
    struct ParamEntry {
        std::string name;
        std::string value;
    };

    std::vector<ParamEntry> m_params;
};
