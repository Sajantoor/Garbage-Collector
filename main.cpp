#include "main.hpp"

int main(int argc, char **argv) {
    GarbageCollector* gc = GarbageCollector::getInstance();
    gc->setStackTop(&argc);
    
    /* 
        Your code here
    */
    
    // Optional line if the user wants to detect and clear memory leaks before program terminates
    gc->collect();
    return 0;
}
