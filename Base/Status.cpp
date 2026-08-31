#include "Status.h"

Status::Status()
    : m_code(0) {
}

Status::Status(int32_t code, const std::string& message)
    : m_code(code)
    , m_message(message) {
}

Status::~Status() {
}
