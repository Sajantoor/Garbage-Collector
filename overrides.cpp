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
    GarbageCollector* gc = new GarbageCollector();
    gc->allocate(pointer, size);

    return pointer;
}

/**
 * Overide the delete operator globally for garbage collection.
 * This is optional but more performant. 
 */ 
void operator delete(void * pointer) {
    std::cout << "Freeing at " << pointer << std::endl;
    free(pointer);
}