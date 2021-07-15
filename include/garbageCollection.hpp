#ifndef GARBAGE_COLLECTION_HPP
#define GARBAGE_COLLECTION_HPP

// This is required for the garbage collection 
#include "GarbageCollector.hpp"
#include "overrides.hpp"

// Macro magic to make it specific to the file 
#define new new(__FILE__, __LINE__)
#define delete std::cout << "Manual delete from " __FILE__ << " at line: " << __LINE__ << std::endl, delete

// Redefine main to include all the neccessary garbage collection stuff.
// To change return type of main change GC_Main's return type
int GC_Main(int argc, char** argv);
#define main(...) \
  main(int argc, char** argv) { \
    GarbageCollector* gc = GarbageCollector::getInstance(); \
    gc->setStackTop(&argc); \
    return GC_Main(argc, argv); \
  }; \
  int GC_Main(__VA_ARGS__)

int GC_Main(int argc, char **argv);

// Last line required for garbage collection ^ 

#endif // GARBAGE_COLLECTION_HPP