#pragma once

#include <cstdint>
#include <string>

namespace NIpse {
    class CRlAgent {
    public:
        // Member variables
        uint32_t m_id = 0;
        std::string m_name;
        bool m_active = false;
        float m_learningRate = 0.01f;
        float m_discountFactor = 0.99f;
        float m_explorationRate = 0.1f;

        // Constructor
        CRlAgent() = default;

        CRlAgent(uint32_t id, const std::string& name)
            : m_id(id), m_name(name), m_active(false),
              m_learningRate(0.01f), m_discountFactor(0.99f),
              m_explorationRate(0.1f) {}

        // Getters
        uint32_t GetId() const { return m_id; }
        const std::string& GetName() const { return m_name; }
        bool IsActive() const { return m_active; }
        float GetLearningRate() const { return m_learningRate; }
        float GetDiscountFactor() const { return m_discountFactor; }
        float GetExplorationRate() const { return m_explorationRate; }

        // Setters
        void SetId(uint32_t id) { m_id = id; }
        void SetName(const std::string& name) { m_name = name; }
        void SetActive(bool active) { m_active = active; }
        void SetLearningRate(float rate) { m_learningRate = rate; }
        void SetDiscountFactor(float factor) { m_discountFactor = factor; }
        void SetExplorationRate(float rate) { m_explorationRate = rate; }

        // Agent operations
        virtual void Initialize() { m_active = true; }
        virtual void Shutdown() { m_active = false; }
        virtual void Update(float deltaTime) {}

        // Check if agent should explore
        bool ShouldExplore() const {
            return (static_cast<float>(rand()) / static_cast<float>(RAND_MAX)) < m_explorationRate;
        }

        // Reset agent state
        void Reset() {
            m_active = false;
            m_learningRate = 0.01f;
            m_discountFactor = 0.99f;
            m_explorationRate = 0.1f;
        }
    };
}


