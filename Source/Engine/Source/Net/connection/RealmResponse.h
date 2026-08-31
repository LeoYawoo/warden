#pragma once

class RealmResponse {
public:
    // Virtual member functions
    virtual void HandleAuthResponse(RealmConnection *connection, uint8_t authResult) = 0;

    virtual void GameServerResult(RealmConnection *connection, const char *a3, const char *a4, const char *a5) = 0;
};


