#include "GarbageCollector.hpp"

GarbageCollector::GarbageCollector() {
    return;
}

GarbageCollector::~GarbageCollector() {
     
}

void GarbageCollector::allocate(void * pointer, std::size_t size) {
    allocation allocation = {size, false};
    PointerMap::value_type pair(pointer, allocation);
    m_allocations.insert(pair);
}

void GarbageCollector::deallocate() {
    
}

void GarbageCollector::collect() {
    
}