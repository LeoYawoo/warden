#pragma once

#include <cstdint>
#include <string>

// Reverse engineered from Warcraft III binary
// JassWar3 manages JASS scripting for Warcraft III

class JassWar3 {
public:
    JassWar3();
    ~JassWar3();

    // Script operations
    bool Initialize();
    void Shutdown();
    bool IsInitialized() const;

    // Script execution
    bool ExecuteScript(const char* script);
    bool LoadScript(const char* fileName);

    // Script state
    bool IsScriptLoaded() const;

protected:
    bool m_initialized;
    bool m_scriptLoaded;
    std::string m_scriptName;
};
