#include "GLWorker.h"
#include "GLCommand.h"
#include "GLDevice.h"
#include "GLTypes.h"

void *GLWorker::Worker(void *userArg) {
    GLWorker *worker = static_cast<GLWorker *>(userArg);

    GLDevice *device = new GLDevice();
    device->Init(nullptr, "GLWorker", 0x10, GLTF_INVALID);

    auto commandsEnd = worker->m_Commands.end();

    while (!worker->m_UnkA0) {
        while (1) {
            worker->m_Mutex1.lock();

            while (worker->m_Commands.begin() == commandsEnd) {
                //pthread_cond_wait(&worker->m_Cond1, &worker->m_Mutex1);
                SleepConditionVariableCS(&worker->m_Cond1, &worker->m_Mutex1.cs, INFINITE);
            }

            worker->m_Mutex2.lock();

            if (worker->m_Commands.begin() == commandsEnd) {
                break;
            }

            GLCommand *command = worker->m_Commands.front();
            worker->m_Commands.pop_front();

            worker->m_Mutex1.unlock();

            if (command) {
                command->Execute(device);
                delete command;
            } else {
                //pthread_cond_signal(&worker->m_Cond2);
                WakeConditionVariable(&worker->m_Cond2);
            }

            worker->m_Mutex2.unlock();

            if (worker->m_UnkA0) {
                goto DONE;
            }
        }

        worker->m_Mutex2.unlock();
        worker->m_Mutex1.unlock();
    }

    DONE:
    delete device;
    return nullptr;
}

DWORD WINAPI SetupThreadFunction(LPVOID lpParameter) {
    GLWorker *worker = static_cast<GLWorker *>(lpParameter);
    worker->Worker(worker);
    return 0;
}

// https://stackoverflow.com/questions/60620003/win32-equivalent-api-for-pthread-cond-wait
// https://stackoverflow.com/questions/63001474/how-to-lockunlock-a-mutex-using-windows-h
// https://cs.gmu.edu/~rcarver/ModernMultithreading/LectureNotes/chapter3noteswin32-2up.pdf
// https://courses.cs.washington.edu/courses/cse410/00au/hw/hw6_mutex.html
// https://stackoverflow.com/questions/34324341/c-win32-thread-createthread-function-not-passing-parameter-correctly
GLWorker::GLWorker(GLDevice *device) : m_Commands() {
    this->m_UnkA0 = 0;
    this->m_UnkA1 = 0;
    this->m_Device = device;
    InitializeConditionVariable(&this->m_Cond1);
    InitializeConditionVariable(&this->m_Cond2);
    //pthread_mutex_init(&this->m_Mutex1, nullptr);
    //pthread_cond_init(&this->m_Cond1, nullptr);
    //pthread_mutex_init(&this->m_Mutex2, nullptr);
    //pthread_cond_init(&this->m_Cond2, nullptr);

    //pthread_create(&this->m_Thread, nullptr, &Worker, this);
    m_Thread = CreateThread(NULL, 0,
                            (LPTHREAD_START_ROUTINE) SetupThreadFunction, this, 0, 0);
}

void GLWorker::Lock() {
    //pthread_mutex_lock(&this->m_Mutex1);
    this->m_Mutex1.lock();
}

void GLWorker::Send(GLCommand *command) {
    this->m_Commands.push_back(command);
    this->m_UnkA1 = 0;
}

void GLWorker::Signal() {
    // pthread_cond_signal(&this->m_Cond1);
    WakeConditionVariable(&this->m_Cond1);
}

void GLWorker::Unlock() {
    //pthread_mutex_unlock(&this->m_Mutex1);
    this->m_Mutex1.unlock();
}

void GLWorker::WaitOnGLObjects() {
    // pthread_mutex_lock(&this->m_Mutex1);
    this->m_Mutex1.lock();

    if (this->m_Commands.begin() == this->m_Commands.end()) {
        GLFlush *command = new GLFlush();
        this->m_Commands.push_back(command);

        this->m_Commands.push_back(nullptr);
    } else {
        auto it = this->m_Commands.begin();

        // TODO some kind of reordering logic for commands

        if (this->m_Commands.begin() == it) {
            GLFlush *command = new GLFlush();
            this->m_Commands.push_back(command);

            this->m_Commands.push_back(nullptr);
        } else {
            GLFlush *command = new GLFlush();
            this->m_Commands.insert(it, command);

            this->m_Commands.insert(it, nullptr);
        }
    }
    WakeConditionVariable(&this->m_Cond1);
    SleepConditionVariableCS(&this->m_Cond2, &this->m_Mutex1.cs, INFINITE);
    // pthread_cond_signal(&this->m_Cond1);
    // pthread_cond_wait(&this->m_Cond2, &this->m_Mutex1);

    this->m_UnkA1 = 1;

    //pthread_mutex_unlock(&this->m_Mutex1);
    this->m_Mutex1.unlock();
}

GLWorker::~GLWorker() {
    WaitForSingleObject(m_Thread, INFINITE);
}
