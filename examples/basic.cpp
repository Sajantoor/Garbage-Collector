#include "../garbageCollection.hpp"
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
    array = new int[50];
    
    gc->collect();
    return 0;
}
