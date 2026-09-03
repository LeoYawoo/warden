#include "WorldCampaign.h"
#include <algorithm>

// Reverse engineered from Warcraft III binary

WorldCampaign::WorldCampaign() : m_initialized(false), m_visible(true) {}
WorldCampaign::~WorldCampaign() { Shutdown(); }

bool WorldCampaign::Initialize() {
    m_initialized = true;
    return true;
}

void WorldCampaign::Shutdown() {
    m_initialized = false;
    m_missions.clear();
}

bool WorldCampaign::IsInitialized() const { return m_initialized; }

const char* WorldCampaign::GetCampaignName() const { return m_campaignName.c_str(); }
void WorldCampaign::SetCampaignName(const char* name) { m_campaignName = name ? name : ""; }

const char* WorldCampaign::GetCampaignDescription() const { return m_campaignDescription.c_str(); }
void WorldCampaign::SetCampaignDescription(const char* description) { m_campaignDescription = description ? description : ""; }

void WorldCampaign::AddMission(const char* name, int32_t missionId) {
    if (!name) return;
    Mission mission;
    mission.name = name;
    mission.missionId = missionId;
    m_missions.push_back(mission);
}

void WorldCampaign::RemoveMission(int32_t missionId) {
    m_missions.erase(
        std::remove_if(m_missions.begin(), m_missions.end(),
            [missionId](const Mission& m) { return m.missionId == missionId; }),
        m_missions.end());
}

size_t WorldCampaign::GetMissionCount() const { return m_missions.size(); }

const char* WorldCampaign::GetMissionName(size_t index) const {
    return (index < m_missions.size()) ? m_missions[index].name.c_str() : nullptr;
}

int32_t WorldCampaign::GetMissionId(size_t index) const {
    return (index < m_missions.size()) ? m_missions[index].missionId : -1;
}

bool WorldCampaign::IsVisible() const { return m_visible; }
void WorldCampaign::SetVisible(bool visible) { m_visible = visible; }
