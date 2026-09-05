#pragma once

// WardenWindow - QOpenGLWindow subclass for GL context management
// Manages OpenGL context lifecycle and forwards events to the engine

#include <QOpenGLWindow>
#include <QOpenGLFunctions>

class WardenWindow : public QOpenGLWindow, protected QOpenGLFunctions {
    Q_OBJECT
public:
    explicit WardenWindow(QWindow *parent = nullptr);
    ~WardenWindow() override;

    // Get the GL functions interface
    QOpenGLFunctions *glFunctions() { return this; }

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    // Input events
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void closeEvent(QCloseEvent *event) override;
};
