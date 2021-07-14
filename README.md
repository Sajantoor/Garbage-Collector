# Garbage Collector 
> A basic garbage collector and memory leak detector in C++

#### Table of Contents
* [About](#About)
    * [API](#API)
* [Getting Started](#Getting-Started)
* [Acknowledgements](#Acknowledgements)

# About
This Garbage Collector is a simple implementation of a **mark and sweep** garbage collector in C++. Unlike other garbage collector implementations in C++ where the user needs to update their code to use it, as they use custom functions such as `gc_new` for garbage collection, this garbage collector just requires the addition of 1 line of code, a header file! It works by overloading the `new` and `delete` operators in all files where the header file is included (ie, where users are using the garbage collector), using some *macro magic*. 

## API 
```cpp
static GarbageCollector* GarbageCollector::getInstance() 
```
The garbage collector class follows a singleton design pattern, where only one of the class exists. This method returns a pointer to its instance.


```cpp
void GarbageCollector::collect()
```
This method runs the mark and sweep garbage collection algorithm, scanning the stack for pointers which determines reachability. Any pointers not found on stack are freed. This function runs automatically when the currently allocated memory reaches some threshold which is set in `garbageCollector.hpp`.

```cpp
void * operator new(std::size_t size, const char * file, const std::size_t line) {
    ...
    // get garbage collector
    GarbageCollector* gc = GarbageCollector::getInstance();
    gc->allocate(pointer, size, file, line);
    ...
    return pointer;
}
```
Override of the new operator, allocates using `malloc()` and follows normal behavior of the function `new`. Calls Garbage Collector's allocation method. This function also gets the file and line where it was called making it easier to find memory leaks.

```cpp
void operator delete(void * pointer) {
    ... 
    // deallocate from garbage collector
    GarbageCollector* gc = GarbageCollector::getInstance(); 
    gc->deallocate(pointer);
}
```
Override of the delete operator, deallocates using `free` and follows normal behavior of the function `delete`. Calls Garbage Collector's deallocate method. This function is optional as unused memory will be deallocated anyways, but calling delete would be more performant.


### Helper functions
It's not recommended to call any of these functions or methods.
```cpp
void GarbageCollector::allocate(void * pointer, std::size_t size, const char* file, std::size_t line)
```
This method is called when `new` or `new[]` is called, this adds the pointer to the hashmap, updates the size used by the garbage collector. 


```cpp
void GarbageCollector::deallocate(void * pointer)
```
This method is called when `delete` or `delete[]` is called. It removes the pointer from the hashmap.


```cpp
void GarbageCollector::setStackTop(void * top);
```
Sets the private variable of the GarbageCollector class `stackTop` to the top of the stack, is called in the beginning of main.


Data Structures: 
```cpp
typedef struct allocation {
    std::size_t size; 
    bool mark; 
    const char* file;
    std::size_t line;
} allocation;
```
This is the data structure used for all memory allocations in the hashmap, allowing for access for the size, its marked state (for the mark and sweep algorithm), what file and line it was allocated on.


## Example
```cpp
#include "../garbageCollection.hpp"

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
    
    // manually running the garbage collector
    gc->collect();
    return 0;
}
```

<!-- TODO: Add how it works -->
<!-- Mark and sweep algorithm -->
<!-- Main macro -->
<!-- Changing the return type of main -->

# Getting Started
Clone this repository
```
git clone https://github.com/Sajantoor/Garbage-Collector.git
```

Add the following line to all the files in your project.
```cpp
#include "garbageCollection.hpp"
```

Run the make file with a main.cpp file
```
make
```

`make debug`: Gives the user information such as where pointers have been allocated, size, etc and when automatic garbage collection has ran and when pointers have been deallocated.

`make leak`: Does not run garbage collection, only detects memory leaks and outputs it to the terminal.

`clean`: Removes all .out files.

# Acknowledgements
This project could not be done without the ability to read of others and most notability the work of [Samuel Williams's journal](https://www.codeotaku.com/journal/2011-09/simple-garbage-collector/index), which taught me a lot about the basics of a simple garbage collector and was the base for this project.