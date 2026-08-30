#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace NIpse {
    class CRlAgentDef {
    public:
        // Member variables
        uint32_t m_id = 0;
        std::string m_name;
        std::string m_description;
        float m_defaultLearningRate = 0.01f;
        float m_defaultDiscountFactor = 0.99f;
        float m_defaultExplorationRate = 0.1f;
        uint32_t m_maxEpisodes = 1000;
        uint32_t m_maxStepsPerEpisode = 100;

        // Constructor
        CRlAgentDef() = default;

        CRlAgentDef(uint32_t id, const std::string& name)
            : m_id(id), m_name(name) {}

        // Getters
        uint32_t GetId() const { return m_id; }
        const std::string& GetName() const { return m_name; }
        const std::string& GetDescription() const { return m_description; }
        float GetDefaultLearningRate() const { return m_defaultLearningRate; }
        float GetDefaultDiscountFactor() const { return m_defaultDiscountFactor; }
        float GetDefaultExplorationRate() const { return m_defaultExplorationRate; }
        uint32_t GetMaxEpisodes() const { return m_maxEpisodes; }
        uint32_t GetMaxStepsPerEpisode() const { return m_maxStepsPerEpisode; }

        // Setters
        void SetId(uint32_t id) { m_id = id; }
        void SetName(const std::string& name) { m_name = name; }
        void SetDescription(const std::string& desc) { m_description = desc; }
        void SetDefaultLearningRate(float rate) { m_defaultLearningRate = rate; }
        void SetDefaultDiscountFactor(float factor) { m_defaultDiscountFactor = factor; }
        void SetDefaultExplorationRate(float rate) { m_defaultExplorationRate = rate; }
        void SetMaxEpisodes(uint32_t episodes) { m_maxEpisodes = episodes; }
        void SetMaxStepsPerEpisode(uint32_t steps) { m_maxStepsPerEpisode = steps; }

        // Validation
        bool IsValid() const {
            return !m_name.empty() && m_defaultLearningRate > 0.0f &&
                   m_defaultDiscountFactor >= 0.0f && m_defaultDiscountFactor <= 1.0f;
        }

        // Reset to defaults
        void Reset() {
            m_defaultLearningRate = 0.01f;
            m_defaultDiscountFactor = 0.99f;
            m_defaultExplorationRate = 0.1f;
            m_maxEpisodes = 1000;
            m_maxStepsPerEpisode = 100;
        }
    };
}


