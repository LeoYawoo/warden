#ifndef APP_MAC_VIEW_H
#define APP_MAC_VIEW_H

#include <string>

struct GLWindowCallbacks;

void AssignEngineViewCallbacks(GLWindowCallbacks *callbacks);

std::string GetEngineViewClass();

#endif
