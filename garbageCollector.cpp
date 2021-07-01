#include "GarbageCollector.hpp"

GarbageCollector::GarbageCollector() {
    
}



GarbageCollector::~GarbageCollector() {
     
}

void GarbageCollector::allocate(void * pointer, std::size_t size) {
    // add to hashmap
    allocation allocation = {size, false};
    PointerMap::value_type pair(pointer, allocation);
    m_allocations.insert(pair);
    std::cout << "Size " << m_allocations.size() << std::endl;
}

void GarbageCollector::deallocate(void * pointer) {
    // remove from hashmap
    m_allocations.erase(pointer);
}

void GarbageCollector::collect() {
    // Garbage collector must be intialized at the top of the stack.
    void * top = this;
    void ** current = (void **) &top;

    std::cout << "Collecting from " << current << " to " << top << std::endl;

    // unmark everything 
    for (PointerMap::iterator root = m_allocations.begin(); root != m_allocations.end(); root++) {
        root->second.mark = false;
    }

    // scan the stack and mark
    while (current <= top) {
        void * pointer = *current;
        std::cout << "Pointer: " << pointer << std::endl;
        // find the allocation in the map with the same value and mark it  
        int allocation = m_allocations.count(pointer);
        // PointerMap::iterator allocation = m_allocations.find(pointer);
        // std::cout  << "Allocation: " << m_allocations.end() << std::endl;
		
		if (allocation == 1) {
			std::cout << "Found allocation " << pointer << " at " << current << std::endl;
			// allocation->second.mark += 1;
		}
		// Move to next pointer
		current++;
    }

    // sweep
    for (PointerMap::iterator root = m_allocations.begin(); root != m_allocations.end(); root++) {
        // if it's marked 
        if (!root->second.mark && root->first != 0) {
            void * pointer = root->first;
            std::cout << "Releasing " << root->second.size << " bytes at " << root->first << std::endl;
            this->deallocate(pointer);
            free(pointer);
        }
    }
}  