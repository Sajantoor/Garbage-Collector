#include "overrides.hpp"

/**
 * Override the new operator globally for garbage collection. 
*/
void * operator new(std::size_t size, std::size_t alloc) {
    // create new pointer with the size
    void * pointer = malloc(size);
     std::cout << "Allocating " << size << " bytes of memory at " << pointer << std::endl;

    // if memory allocation fails, throw bad alloc exception
    if (pointer == nullptr) {
        std::bad_alloc exception;
        throw(exception);
    }

    if (!alloc) {
        return pointer;
    }

    // create new garbage collector
    GarbageCollector* gc = GarbageCollector::getInstance();
    std::cout << "Getting instance of gc " << gc << std::endl;

    gc->allocate(pointer, size);

    return pointer;
}

/**
 * Overide the delete operator globally for garbage collection.
 * This is optional but more performant. 
 */ 
void operator delete(void * pointer, std::size_t alloc) {
    if (pointer == nullptr) 
        return;

    std::cout << "Freeing at " << pointer << std::endl;
    // deallocate from garbage collector
    GarbageCollector* gc = GarbageCollector::getInstance(); 
    std::cout << "Getting instance of gc del " << gc << std::endl;

    free(pointer);
    gc->deallocate(pointer);
}