#include "net/Poll.h"
#include "net/connection/RealmConnection.h"

int32_t PollNet(const void *a1, void *a2) {
    RealmConnection::PollNet();

    // TODO

    return 1;
}
