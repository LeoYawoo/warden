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
    // TODO: Implement network synchronization
}

void NetUnit::Deserialize(const uint8_t* data, uint32_t size) {
    (void)data; (void)size;
    // TODO: Implement deserialization
}

uint32_t NetUnit::Serialize(uint8_t* data, uint32_t maxSize) const {
    (void)data; (void)maxSize;
    // TODO: Implement serialization
    return 0;
}
