#include "net/login/Login.h"
#include "net/login/LoginResponse.h"
#include "StormMac/String.h"
#include <cstring>
#include "Common/datastore/CDataStore.h"

Login::~Login() {
    // TODO
}

bool Login::IsReconnect() {
    return this->m_reconnect;
}

bool Login::OnlineIdle() {
    // TODO

    return true;
}

void Login::RealmListResult(CDataStore *msg) {
    if (!msg || !msg->IsFinal()) {
        this->m_loginResponse->HandleRealmData(4, nullptr);
    } else {
        this->m_loginResponse->HandleRealmData(0, msg);
    }
}

void Login::SetLogonCreds(const char *accountName, const char *password) {
    SStrCopy(this->m_accountName, accountName, 1280);

    if (this->m_password) {
        memset(this->m_password, 0, SStrLen(this->m_password));
        SMemFree(this->m_password, __FILE__, __LINE__, 0x0);
    }

    this->m_password = SStrDupA(password, __FILE__, __LINE__);
}
