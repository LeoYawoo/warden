#include "WardenWindow.h"
#include "CGxDeviceOpenGL/CGxDeviceOpenGl.h"
#include "Screen.h"
#include "Gx.h"
#include "event/Event.h"

// Reverse engineered from Warcraft III binary
// WardenWindow replaces the Mac AGL context with Qt's QOpenGLWindow

extern CGxDevice *g_theGxDevicePtr;

WardenWindow::WardenWindow(QWindow *parent)
    : QOpenGLWindow(NoPartialUpdate, parent) {
    setTitle("Warcraft III");
}

WardenWindow::~WardenWindow() {
    makeCurrent();
    // GL cleanup will be handled by the engine
}

void WardenWindow::initializeGL() {
    // Initialize OpenGL function pointers via Qt
    initializeOpenGLFunctions();

    // Set global GL functions for the engine
    GxSetGLFunctions(this);

    // Pass GL functions to the device
    auto *device = dynamic_cast<CGxDeviceOpenGl *>(g_theGxDevicePtr);
    if (device) {
        device->SetGLFunctions(this);
        device->SetWindowHandle(reinterpret_cast<void *>(winId()));
    }

    // Set initial viewport
    glViewport(0, 0, width(), height());
}

void WardenWindow::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);
}

void WardenWindow::paintGL() {
    // Delegate to the engine's OnPaint
    // The Screen module handles the actual rendering
    OnPaint(nullptr, nullptr);

    // Request next frame (game loop driven)
    update();
}

void WardenWindow::keyPressEvent(QKeyEvent *event) {
    // TODO: Forward to engine input system
    QOpenGLWindow::keyPressEvent(event);
}

void WardenWindow::keyReleaseEvent(QKeyEvent *event) {
    // TODO: Forward to engine input system
    QOpenGLWindow::keyReleaseEvent(event);
}

void WardenWindow::mousePressEvent(QMouseEvent *event) {
    // TODO: Forward to engine input system
    QOpenGLWindow::mousePressEvent(event);
}

void WardenWindow::mouseReleaseEvent(QMouseEvent *event) {
    // TODO: Forward to engine input system
    QOpenGLWindow::mouseReleaseEvent(event);
}

void WardenWindow::mouseMoveEvent(QMouseEvent *event) {
    // TODO: Forward to engine input system
    QOpenGLWindow::mouseMoveEvent(event);
}

void WardenWindow::closeEvent(QCloseEvent *event) {
    EventPostClose();
    QOpenGLWindow::closeEvent(event);
}
