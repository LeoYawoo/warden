#pragma once

#include <cstdint>

void OsCreateDirectory(const char *, int32_t);

void OsBuildFontFilePath(const char *, char *, size_t);

char *OsPathFindExtensionWithDot(char *);


