#ifndef OVERRIDES_HPP 
#define OVERRIDES_HPP 

#include <iostream>
#include "GarbageCollector.hpp"

extern void * operator new(std::size_t size, const char * file, const std::size_t line);
extern void * operator new[](std::size_t size, const char * file, const std::size_t line);
extern void operator delete(void * pointer);
extern void operator delete[](void * pointer);

#endif // OVERRIDES_HPP