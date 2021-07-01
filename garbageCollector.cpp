#include "GarbageCollector.hpp"

GarbageCollector::GarbageCollector() {}

GarbageCollector::~GarbageCollector() {}

void GarbageCollector::allocate(void * pointer, std::size_t size) {
    // add to hashmap
    allocation allocation = {size, false};
    PointerMap::value_type pair(pointer, allocation);
    m_allocations.insert(pair);
}

void GarbageCollector::deallocate(void * pointer) {
    // find pointer in hashmap
    PointerMap::iterator allocation = m_allocations.find(pointer);

    if (allocation != m_allocations.end()) {
        m_allocations.erase(allocation);
    }

    // else it's not in the hashmap, just free
    delete pointer;
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
        PointerMap::iterator allocation = m_allocations.find(pointer);
		
		if (allocation != m_allocations.end()) {
			std::cout << "Found allocation " << pointer << " at " << current << std::endl;
			allocation->second.mark += 1;
		}
		// Move to next pointer
		current++;
    }

    // sweep
    for (PointerMap::iterator root = m_allocations.begin(), next_it = root; root != m_allocations.end(); root = next_it) {
        // https://stackoverflow.com/questions/6092642/how-to-remove-a-key-from-hashmap-while-iterating-over-it
        // need this because removing during iteration causes seg fault? 
        ++next_it; 
        
        if (!root->second.mark && root->first != nullptr) {
            void * pointer = root->first;
            std::cout << "Releasing " << root->second.size << " bytes at " << root->first << std::endl;
            delete pointer;
            m_allocations.erase(root);
        }
    }
}  