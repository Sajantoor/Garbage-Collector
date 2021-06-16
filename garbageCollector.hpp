#ifndef GARBAGE_COLLECTOR_HPP
#define GARBAGE_COLLECTOR_HPP

#include <iostream> 
#include <map> 

class GarbageCollector { 
    public: 
        // // constructor -> Singleton design 
        GarbageCollector();  
        // destructor
        ~GarbageCollector(); 

        // allocate memory  
        void allocate(void * pointer, std::size_t size); 
         // when delete is called deallocate memory from the garbage collector
        void deallocate();

        // run mark and sweep algorithm and garbage collect.
        void collect(); 

    protected: 
        // memory allocation struct
        typedef struct allocation {
            std::size_t size; 
            bool mark; 
        } allocation;

        // temporary hashmap for collecting 
        typedef std::map<void *, allocation> PointerMap; 
        PointerMap m_allocations;
};

#endif // GARBAGE_COLLECTOR_HPP