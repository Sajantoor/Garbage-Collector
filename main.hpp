#ifndef MAIN_HPP
#define MAIN_HPP

// This is required for the garbage collection 
#include "GarbageCollector.hpp"
#include "overrides.hpp"

// Macro magic to make it specific to the file 
#define new new(__FILE__, __LINE__)
#define delete std::cout << "Manual delete from " __FILE__ << " at line: " << __LINE__ << std::endl, delete
GarbageCollector* GarbageCollector::instance;

// Redefine main to include all the neccessary garbage collection stuff.

/*
int gc_main(int argc, char **argv);

#define main(...) \
  main(int argc, char** argv) { \
    GarbageCollector* gc = GarbageCollector::getInstance(); \
    gc->setStackTop(&argc); \
    return gc_main(argc, argv); \
  }; \
  int gc_main(int argc, char **argv)
*/ 
// Last line required for garbage collection ^ 

#endif // MAIN_HPP