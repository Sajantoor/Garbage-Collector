#include "main.hpp"
#include "GarbageCollector.hpp"
#include "overrides.hpp"

// Macro magic to make it specific to the file 
#define new new(__FILE__, __LINE__)
#define delete std::cout << "Manual delete from " __FILE__ << " at line: " << __LINE__ << std::endl, delete
// I have no idea why but this makes it work. OPTIMIZE FIGURE OUT ANOTHER WAY.
GarbageCollector* GarbageCollector::instance;

int main() {
    // IMPORTANT: Clear garbage collector on top of stack, first line in main();
    GarbageCollector* gc = GarbageCollector::getInstance();
    // allocating bytes to memory
    int *array = new int;
    int *arra2y = new int;
    int *array2 = new int;
    int *array3 = new int;
    int *array5 = new int;
    int *arrayProper = new int [5];
    int* reference = arrayProper;

    std::cout << "Collect garbage" << std::endl;
    gc->collect();
    return 0;
}
