#include "main.hpp"
#include "GarbageCollector.hpp"
#include "overrides.hpp"

// Macro magic to make it specific to the file 
#define new new(__FILE__, __LINE__)
#define delete std::cout << "Manual delete from " __FILE__ << " at line: " << __LINE__ << std::endl, delete
// I have no idea why but this makes it work. OPTIMIZE FIGURE OUT ANOTHER WAY.
GarbageCollector* GarbageCollector::instance;

// allocate int array of size 5
int* allocate() {
    int* array = new int[5];
    return array;
}

int main(int argc, char **argv) {
    GarbageCollector* gc = GarbageCollector::getInstance();
    gc->setStackTop(&argc);

    // allocating bytes to memory
    for (int i = 0; i < 10; i++) {
        // memory leak that the compiler won't warn your about since it's not being referenced.
        allocate();
    }

    int* array = new int[25];
    int* reference = array;
    reference[0] = 5;
    
    std::cout << "Collect garbage" << std::endl;
    gc->collect();
    return 0;
}
