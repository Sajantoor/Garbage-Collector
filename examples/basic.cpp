#include "../main.hpp"

// allocate int array of size 5
int* allocate() {
    int* array = new int[5];
    return array;
}

int gc_main(int argc, char **argv) {
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
    
    gc->collect();
    return 0;
}
