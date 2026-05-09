#include <iostream>
#include <QGuiApplication>
#include <QSurfaceFormat>
#include "Event/Event.h"
#include "Storm/StormInit.h"
#include "Game/Client.h"



int main(int argc, char **argv) {
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
