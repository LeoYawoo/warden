#include <QApplication>
#include <QSurfaceFormat>
#include "Engine/Source/Gx/WardenWindow.h"
#include "Engine/Source/Event/Event.h"
#include "StormMac/StormInit.h"
#include "Game/Client.h"

int main(int argc, char **argv) {
    QSurfaceFormat fmt;
    fmt.setSwapInterval(0);
    fmt.setDepthBufferSize(24);
    fmt.setStencilBufferSize(8);
    QSurfaceFormat::setDefaultFormat(fmt);

    QApplication app(argc, argv);

    // Create the OpenGL window
    WardenWindow window;
    window.resize(1024, 768);
    window.show();

    StormInitialize();

    if (InitializeGlobal()) {
        EventDoMessageLoop();
    }

    return app.exec();
}
