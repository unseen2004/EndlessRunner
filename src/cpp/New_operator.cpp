#include "headers/new_operator.h"
#include <cstdlib>

void* operator new[](std::size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line) {
    return std::malloc(size);
}

void* operator new[](std::size_t size, std::size_t alignment, std::size_t alignmentOffset, const char* pName, int flags, unsigned debugFlags, const char* file, int line) {
    return std::malloc(size);
}