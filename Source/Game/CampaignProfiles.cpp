#include "CampaignProfiles.h"

// Reverse engineered from Warcraft III binary

CampaignProfiles::CampaignProfiles() : m_initialized(false) {}
CampaignProfiles::~CampaignProfiles() { Shutdown(); }

bool CampaignProfiles::Initialize() {
    m_initialized = true;
    return true;
}

void CampaignProfiles::Shutdown() {
    m_initialized = false;
    m_profiles.clear();
}

bool CampaignProfiles::IsInitialized() const { return m_initialized; }

void CampaignProfiles::AddProfile(const char* name, int32_t profileId) {
    if (!name) return;
    Profile profile;
    profile.name = name;
    profile.profileId = profileId;
    m_profiles.push_back(profile);
}

void CampaignProfiles::RemoveProfile(int32_t profileId) {
    m_profiles.erase(
        std::remove_if(m_profiles.begin(), m_profiles.end(),
            [profileId](const Profile& p) { return p.profileId == profileId; }),
        m_profiles.end());
}

size_t CampaignProfiles::GetProfileCount() const { return m_profiles.size(); }

const char* CampaignProfiles::GetProfileName(int32_t profileId) const {
    for (const auto& profile : m_profiles) {
        if (profile.profileId == profileId) {
            return profile.name.c_str();
        }
    }
    return nullptr;
}
