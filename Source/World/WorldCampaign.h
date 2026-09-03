#pragma once

#include <cstdint>
#include <string>
#include <vector>

// Reverse engineered from Warcraft III binary
// WorldCampaign manages campaign data

class WorldCampaign {
public:
    WorldCampaign();
    ~WorldCampaign();

    // Campaign operations
    bool Initialize();
    void Shutdown();
    bool IsInitialized() const;

    // Campaign properties
    const char* GetCampaignName() const;
    void SetCampaignName(const char* name);

    const char* GetCampaignDescription() const;
    void SetCampaignDescription(const char* description);

    // Campaign missions
    void AddMission(const char* name, int32_t missionId);
    void RemoveMission(int32_t missionId);
    size_t GetMissionCount() const;
    const char* GetMissionName(size_t index) const;
    int32_t GetMissionId(size_t index) const;

    // Campaign state
    bool IsVisible() const;
    void SetVisible(bool visible);

protected:
    struct Mission {
        std::string name;
        int32_t missionId;
    };

    bool m_initialized;
    bool m_visible;
    std::string m_campaignName;
    std::string m_campaignDescription;
    std::vector<Mission> m_missions;
};
