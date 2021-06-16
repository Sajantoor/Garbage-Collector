#include "main.hpp"
#include "GarbageCollector.hpp"
#include "overrides.hpp"

GarbageCollector* collector = new GarbageCollector();

// Macro magic to make it specific to the file 
#define __ALLOC__ 1
#define new new(__ALLOC__)

int main() {
    // allocating bytes to memory
    int *array = new int;
    std::cout << "hello world" << std::endl;
    return 0;
}
