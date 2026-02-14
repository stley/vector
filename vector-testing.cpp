#include <iostream>
#include "vector.hpp"
#include <cstdarg>

berkeley::vector<int> firstOne;


void printLine(const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    printf("\n");
    va_end(args);
}

int main()
{
    std::cout << "Hello, from vector!\n";
    //firstOne = new berkeley::vector<int>();
    printLine("Vector size: %d elements (%d bytes) | Capacity: %d elements (%d bytes)", firstOne.size(), firstOne.byte_size(), firstOne.capacity(), firstOne.byte_cap());

    size_t vector_size = firstOne.capacity();
    for (int i = 0; i < 100; i++)
    {
        firstOne.push_back(i+3);
    }   

    firstOne.resize(10);

    firstOne.push_back(34);
    for (int i = 0; i < firstOne.size(); i++)
    {
        std::cout << "at " << i << " " << (firstOne.at(i)) << "\n";
    }

    printLine("Vector size: %d elements (%d bytes) | Capacity: %d elements (%d bytes)", firstOne.size(), firstOne.byte_size(), firstOne.capacity(), firstOne.byte_cap());
    return 0;
}
