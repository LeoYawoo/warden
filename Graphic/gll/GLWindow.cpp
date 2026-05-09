#include "GLWindow.h"
#include "GLContext.h"
#include "Storm/Autorelease.h"
#include "Storm/Debug.h"
#include <cmath>
//#include <QOpenGLWindow>
#include <QSurfaceFormat>
#include <QDebug>


GLWindowCallbacks DefaultCallbacks = {
        // TODO
};

bool GLWindow::CanEnterFullscreenMode() {
    return true;
}


void GLWindow::EnterFullscreenMode() {
    m_FullscreenWindow = this;
    this->showFullScreen();
}

void GLWindow::ExitFullscreenMode() {
    if (m_FullscreenWindow) {
        this->showNormal();
        m_FullscreenWindow = nullptr;
    }
}

GLWindow::GLWindow( GLWindowCallbacks *callbacks) {//QScreen *primaryScreen,
    this->SetCallbacks(callbacks);
}

CRect GLWindow::GetRect(void) {
    return CRect();
}

void GLWindow::Show(void) {
    this->create();
    this->QWindow::show();
}

void GLWindow::Resize(uint32_t width, uint32_t height) {
    this->QWindow::resize(width, height);
}

void GLWindow::SetTitle(const char *string) {
    this->QWindow::setTitle(QString::fromUtf8(string));
}

void GLWindow::CreateView(void) {
    this->create();
}

HWND GLWindow::GetNSView(void) {
    return nullptr;
}

CRect GLWindow::GetBackingRect() {
    return CRect();
}

void GLWindow::SetCallbacks(GLWindowCallbacks *callbacks) {
    if (callbacks) {
        this->m_Callbacks = callbacks;
        this->m_ActiveCallbacks = callbacks;
    } else {
        this->m_Callbacks = &DefaultCallbacks;
        this->m_ActiveCallbacks = &DefaultCallbacks;
    }
}

void GLWindow::SetOpenGLContext(GLContext *context) {
    setSurfaceType(QSurface::OpenGLSurface);
    this->setFormat(QSurfaceFormat::defaultFormat());
    m_Context = context;
//    m_Context->SetContextFormat(fmt, 24);
//
//    m_Context->create();
//
//    if (!m_Context->isValid()) {
//        qCritical() << "The OpenGL context is invalid!"; //I allways get this message
//    }
//
//    qDebug() << "Window format version is: " << this->format().majorVersion() << "." << this->format().minorVersion();
//    qDebug() << "Context format version is: " << m_Context->format().majorVersion() << "."
//             << m_Context->format().minorVersion();
}

int32_t GLWindow::GetWidth(void) {
    return this->QWindow::width();
}

int32_t GLWindow::GetHeight(void) {
    return this->QWindow::height();
}

int32_t GLWindow::GetBackingWidth() {
    return this->QWindow::width() * this->devicePixelRatio();
}

int32_t GLWindow::GetBackingHeight() {
    return this->QWindow::height() * this->devicePixelRatio();
}







