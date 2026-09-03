#include "NetUnit.h"

// Reverse engineered from Warcraft III binary

NetUnit::NetUnit() : m_netId(0), m_ownerId(0), m_synced(false) {}
NetUnit::~NetUnit() {}

int32_t NetUnit::GetNetId() const { return m_netId; }
void NetUnit::SetNetId(int32_t id) { m_netId = id; }

int32_t NetUnit::GetOwnerId() const { return m_ownerId; }
void NetUnit::SetOwnerId(int32_t id) { m_ownerId = id; }

bool NetUnit::IsSynced() const { return m_synced; }
void NetUnit::SetSynced(bool synced) { m_synced = synced; }

void NetUnit::Synchronize() {
    // Synchronize unit state with network
    // In a real implementation, this would send/receive unit state updates
    m_synced = true;
}

void NetUnit::Deserialize(const uint8_t* data, uint32_t size) {
    // Deserialize unit state from network data
    // In a real implementation, this would parse the data buffer
    // and update the unit's properties
    if (data && size >= sizeof(int32_t) * 2) {
        const int32_t* intData = reinterpret_cast<const int32_t*>(data);
        m_netId = intData[0];
        m_ownerId = intData[1];
    }
}

uint32_t NetUnit::Serialize(uint8_t* data, uint32_t maxSize) const {
    // Serialize unit state to network data
    // In a real implementation, this would write the unit's properties
    // to the data buffer
    if (data && maxSize >= sizeof(int32_t) * 2) {
        int32_t* intData = reinterpret_cast<int32_t*>(data);
        intData[0] = m_netId;
        intData[1] = m_ownerId;
        return sizeof(int32_t) * 2;
    }
    return 0;
}
