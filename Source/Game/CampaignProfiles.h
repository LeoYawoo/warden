#pragma once

#include <cstdint>
#include <string>
#include <vector>

// Reverse engineered from Warcraft III binary
// CampaignProfiles manages campaign profiles

class CampaignProfiles {
public:
    CampaignProfiles();
    ~CampaignProfiles();

    // Profile operations
    bool Initialize();
    void Shutdown();
    bool IsInitialized() const;

    // Profile management
    void AddProfile(const char* name, int32_t profileId);
    void RemoveProfile(int32_t profileId);
    size_t GetProfileCount() const;

    // Profile queries
    const char* GetProfileName(int32_t profileId) const;

protected:
    struct Profile {
        std::string name;
        int32_t profileId;
    };

    bool m_initialized;
    std::vector<Profile> m_profiles;
};
