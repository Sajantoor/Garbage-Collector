#include "GarbageCollector.hpp"
// #define DEBUG // for prints

GarbageCollector::GarbageCollector() {}

GarbageCollector::~GarbageCollector() {
    // clears all allocations
    m_allocations.clear();
}

void GarbageCollector::allocate(void * pointer, std::size_t size, const char* file, std::size_t line) {
    // add to data to hashmap
    allocation allocation = {size, false, file, line};
    PointerMap::value_type pair(pointer, allocation);
    m_allocations.insert(pair);
    // update garbage collection size
    this->size += size;
    
    // Don't need automatic garbage collection when trying to look only for memory leaks
    #ifndef LEAK 
        // run garbage collection automatically if size is greater than max size
        if (this->size > this->maxSize) {
            #ifdef DEBUG
                std::cout << "Running automatic garbage collection." << std::endl;
            #endif
            this->collect();
        }
    #endif
}

void GarbageCollector::deallocate(void * pointer) {
    // find pointer in hashmap
    PointerMap::iterator allocation = m_allocations.find(pointer);

    if (allocation != m_allocations.end()) {
        // update size
        this->size -= allocation->second.size;
        m_allocations.erase(allocation);
    }

    // if it's not in hashmap free the pointer, free pointer regardless
    free(pointer);
    pointer = nullptr;
}

void GarbageCollector::collect() {
    // unmark everything 
    for (PointerMap::iterator root = m_allocations.begin(); root != m_allocations.end(); root++) {
        root->second.mark = false;
    }

    void* top = this->stackTop;
    void ** current = (void **)&top;

    #ifdef DEBUG 
        std::cout << "Collecting from " << current << " to " << top << std::endl;
    #endif

    // go over stack and mark if any pointer is found in stack
    for (; current < top; current++) {
        void* pointer = *current;
        PointerMap::iterator allocation = m_allocations.find(pointer);

        // if alocation is found mark it as it is "reachable"
		if (allocation != m_allocations.end()) {
            #ifdef DEBUG 
			    std::cout << "Found allocation " << pointer << " at " << allocation->second.file << " " << allocation->second.line << std::endl;
            #endif

			allocation->second.mark = true;
		}
    }

    // sweep anything that's not marked.
    for (PointerMap::iterator root = m_allocations.begin(), next_it = root; root != m_allocations.end(); root = next_it) {
        // https://stackoverflow.com/questions/6092642/how-to-remove-a-key-from-hashmap-while-iterating-over-it
        // need this because removing during iteration causes seg fault? 
        ++next_it; 
        
        if (!root->second.mark && root->first != nullptr) {
            void * pointer = root->first;
            #ifdef DEBUG
                std::cout << "Memory leak detected: Bytes " << root->second.size << " at " << root->first << " from " << root->second.file << ":" << root->second.line << std::endl;
            #endif

            #ifdef LEAK 
                std::cout << "Memory leak detected: Bytes " << root->second.size << " at " << root->first << " from " << root->second.file << ":" << root->second.line << std::endl;
            #endif
            // update size
            this->size -= root->second.size;
            free(pointer);
            m_allocations.erase(root);
        }
    }
}  

void GarbageCollector::setStackTop(void * top) {
    this->stackTop = top;
}