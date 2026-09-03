#pragma once

#include <cstdint>

// Forward declarations
class CUnit;

// Reverse engineered from Warcraft III binary
// NetUnit manages network unit synchronization

class NetUnit {
public:
    NetUnit();
    ~NetUnit();

    // Network properties
    int32_t GetNetId() const;
    void SetNetId(int32_t id);

    int32_t GetOwnerId() const;
    void SetOwnerId(int32_t id);

    // Network state
    bool IsSynced() const;
    void SetSynced(bool synced);

    // Network operations
    void Synchronize();
    void Deserialize(const uint8_t* data, uint32_t size);
    uint32_t Serialize(uint8_t* data, uint32_t maxSize) const;

protected:
    int32_t m_netId;
    int32_t m_ownerId;
    bool m_synced;
};
