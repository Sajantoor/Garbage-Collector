#ifndef GARBAGE_COLLECTOR_HPP
#define GARBAGE_COLLECTOR_HPP

#include <iostream> 
#include <map> 

// Max memory size in bytes
#define SIZE 512;

class GarbageCollector { 
    private: 
        // private constructor -> Singleton design 
        GarbageCollector();  
        static GarbageCollector* instance;
        void* stackTop = nullptr;

        unsigned int size = 0; // size threshold to determine when to automatically run garbage collector 
        unsigned int maxSize = SIZE; // set size threshold to be 128 bytes 

    public: 
        // get the instance of the garbage collector -> singleton design
        static GarbageCollector* getInstance() {
            if (instance == nullptr)
                    instance = new GarbageCollector();
            return instance;
        }
        // destructor
        ~GarbageCollector(); 

        // allocate memory  
        void allocate(void * pointer, std::size_t size, const char* file, std::size_t line); 
         // when delete is called deallocate memory from the garbage collector
        void deallocate(void * pointer);
        
        // run mark and sweep algorithm and garbage collect.
        void collect(); 

        // set the top of the stack
        void setStackTop(void * top);

    protected: 
        // memory allocation struct
        typedef struct allocation {
            std::size_t size; 
            bool mark; 
            const char* file;
            std::size_t line;
        } allocation;

        // temporary hashmap for collecting 
        typedef std::map<void *, allocation> PointerMap; 
        PointerMap m_allocations;
};

#endif // GARBAGE_COLLECTOR_HPP