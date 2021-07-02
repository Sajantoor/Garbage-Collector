#include "GarbageCollector.hpp"

GarbageCollector::GarbageCollector() {}

GarbageCollector::~GarbageCollector() {
    // clears all allocations
    m_allocations.clear();
}

void GarbageCollector::allocate(void * pointer, std::size_t size, const char* file, std::size_t line) {
    // add to hashmap
    allocation allocation = {size, false, file, line};
    PointerMap::value_type pair(pointer, allocation);
    m_allocations.insert(pair);
}

void GarbageCollector::deallocate(void * pointer) {
    // find pointer in hashmap
    PointerMap::iterator allocation = m_allocations.find(pointer);

    if (allocation != m_allocations.end()) {
        m_allocations.erase(allocation);
    }

    // if it's not in hashmap free the pointer, free pointer regardless
    free(pointer);
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

    // scan the stack and mark anything on stack
    while (current <= top) {
        void * pointer = *current;
        std::cout << "Pointer: " << pointer << std::endl;
        PointerMap::iterator allocation = m_allocations.find(pointer);
		
		if (allocation != m_allocations.end()) {
			std::cout << "Found allocation " << pointer << " at " << current << std::endl;
			allocation->second.mark = true;
		}
		// Move to next pointer
		current++;
    }

    // sweep anything that's not marked.
    for (PointerMap::iterator root = m_allocations.begin(), next_it = root; root != m_allocations.end(); root = next_it) {
        // https://stackoverflow.com/questions/6092642/how-to-remove-a-key-from-hashmap-while-iterating-over-it
        // need this because removing during iteration causes seg fault? 
        ++next_it; 
        
        if (!root->second.mark && root->first != nullptr) {
            void * pointer = root->first;
            std::cout << "Memory leak detected: Releasing " << root->second.size << " bytes at " << root->first << " from " << root->second.file << " at line: " << root->second.line << std::endl;
            free(pointer);
            m_allocations.erase(root);
        }
    }
}  