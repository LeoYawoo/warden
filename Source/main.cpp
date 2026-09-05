#include <iostream>
#include <cstdio>
#include <windows.h>
#include <QGuiApplication>
#include <QSurfaceFormat>
#include "Engine/Source/Event/Event.h"
#include "StormMac/StormInit.h"
#include "Game/Client.h"



int main(int argc, char **argv) {
    AllocConsole();
    freopen("CONOUT$", "w", stdout);
    freopen("CONOUT$", "w", stderr);
    fprintf(stderr, "=== warden starting ===\n");
    fflush(stderr);

    QSurfaceFormat fmt;
    fmt.setSwapInterval(0);
    QSurfaceFormat::setDefaultFormat(fmt);

    QGuiApplication app(argc, argv);
    StormInitialize();

    // TODO
    // - error log setup
    // - misc other setup

    if (InitializeGlobal()) {
        EventDoMessageLoop();

        // TODO
        // sub_406B70();
    }
    // TODO
    // - misc cleanup
    return app.exec();
}
