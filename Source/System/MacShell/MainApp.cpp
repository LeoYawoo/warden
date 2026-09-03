#include "MainApp.h"

// Reverse engineered from Warcraft III binary

MainApp::MainApp() : m_initialized(false), m_running(false) {}
MainApp::~MainApp() { Shutdown(); }

bool MainApp::Initialize() {
    m_initialized = true;
    m_running = true;
    return true;
}

void MainApp::Shutdown() {
    m_initialized = false;
    m_running = false;
}

bool MainApp::IsInitialized() const { return m_initialized; }

const char* MainApp::GetAppName() const { return m_appName.c_str(); }
void MainApp::SetAppName(const char* name) { m_appName = name ? name : ""; }

const char* MainApp::GetVersion() const { return m_version.c_str(); }
void MainApp::SetVersion(const char* version) { m_version = version ? version : ""; }

bool MainApp::IsRunning() const { return m_running; }
void MainApp::SetRunning(bool running) { m_running = running; }
