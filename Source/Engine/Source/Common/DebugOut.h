#pragma once
#include <cstdio>
#include <sstream>
#define LOG(fmt, ...) do { fprintf(stderr, fmt "\n", ##__VA_ARGS__); fflush(stderr); } while(0)
#define LOGS(msg) do { fprintf(stderr, "%s\n", msg); fflush(stderr); } while(0)
