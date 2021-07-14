#include "overrides.hpp"
// #define DEBUG // for printing

/**
 * Same allocation logic for both new and new[]
*/
void * allocation(std::size_t size, const char * file, const std::size_t line) {
    // create new pointer with the size
    void * pointer = malloc(size);

    #ifdef DEBUG
        std::cout << "Allocating " << size << " bytes of memory at " << pointer << " from " << file << " at line: " << line << std::endl;
    #endif

    // if memory allocation fails, throw bad alloc exception
    if (pointer == nullptr) {
        std::bad_alloc exception;
        throw(exception);
    }

    // get garbage collector
    GarbageCollector* gc = GarbageCollector::getInstance();
    gc->allocate(pointer, size, file, line);
    
    return pointer;
}

/**
 * Override the new operator globally for garbage collection. 
*/
void * operator new(std::size_t size, const char * file, const std::size_t line) {
    return allocation(size, file, line);
}

/**
 * Override the new operator globally for garbage collection. 
*/
void * operator new[](std::size_t size, const char * file, const std::size_t line) {
    return allocation(size, file, line);
}

/**
 * Same deallocation logic for delete and delete[]
*/
void deallocate(void * pointer) {
    if (pointer == nullptr) {
        std::cout << "Attempted to delete nullptr" << std::endl;
        return;
    }
    // deallocate from garbage collector
    GarbageCollector* gc = GarbageCollector::getInstance(); 
    gc->deallocate(pointer);
}

/**
 * Overide the delete operator globally for garbage collection.
 * This is optional but more performant. 
 */ 
void operator delete(void * pointer) {
    deallocate(pointer);
}

/**
 * Overide the delete operator globally for garbage collection.
 * This is optional but more performant. 
 */ 
void operator delete[](void * pointer) {
    deallocate(pointer);
}