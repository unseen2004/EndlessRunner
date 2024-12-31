#ifndef NEW_OPERATOR_H
#define NEW_OPERATOR_H

#include <cstddef>

void* operator new[](std::size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line);
void* operator new[](std::size_t size, std::size_t alignment, std::size_t alignmentOffset, const char* pName, int flags, unsigned debugFlags, const char* file, int line);

#endif // NEW_OPERATOR_H