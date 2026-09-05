#pragma once

#include "Engine/Source/Net/Connection.h"

class ClientRealmResponseAdapter : public RealmResponse {
public:
    // Virtual member functions
    virtual void HandleAuthResponse(RealmConnection *realmConnection, uint8_t authResult);

    virtual void GameServerResult(RealmConnection *realmConnection, const char *a2, const char *a3, const char *a4) {};
};


