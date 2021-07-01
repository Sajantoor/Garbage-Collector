#include "main.hpp"
#include "GarbageCollector.hpp"
#include "overrides.hpp"

// Macro magic to make it specific to the file 
#define __ALLOC__ 1
#define new new(__ALLOC__)
#define delete delete(__ALLOC__)

// I have no idea why but this makes it work. OPTIMIZE FIGURE OUT ANOTHER WAY.
GarbageCollector* GarbageCollector::instance;

int main() {
    // IMPORTANT: Clear garbage collector on top of stack, first line in main();
    GarbageCollector* gc = GarbageCollector::getInstance();
    std::cout << "Getting instance of gc " << gc << std::endl;

    // allocating bytes to memory
    int *array = new int;
    int *arra2y = new int;
    int *array2 = new int;
    int *array3 = new int;
    int *array5 = new int;

    std::cout << "hello world" << std::endl;
    gc->collect();
    std::cout << "hello world2" << std::endl;
    return 0;
}
