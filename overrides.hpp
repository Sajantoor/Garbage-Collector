#ifndef OVERRIDES_HPP 
#define OVERRIDES_HPP 

#include <iostream>
#include "GarbageCollector.hpp"

extern void * operator new(std::size_t size, std::size_t alloc);
extern void operator delete(void * pointer);

#endif // OVERRIDES_HPP