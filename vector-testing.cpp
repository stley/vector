#include <iostream>
#include "vector.hpp"
#include <cstdarg>

berkeley::vector<int> Integers;
berkeley::vector<float> Floats;
berkeley::vector<double> Doubles;
berkeley::vector<double*> Pointers;

struct Person
{
    std::string name;
    int age = 0;
    bool isCool = true;
};

//berkeley::vector<Person> People;

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
    //Integers = new berkeley::vector<int>();
    //printLine("Vector size: %d elements (%d bytes) | Capacity: %d elements (%d bytes)", Integers.size(), Integers.byte_size(), Integers.capacity(), Integers.byte_cap());

    //size_t vector_size = Integers.capacity();
    Integers.resize(5);
    Floats.resize(5);
    Doubles.resize(5);
    for (int i = 0; i < 10; i++)
    {
        Integers.push_back(i+3);
        Floats.push_back(1.3+i);
        Doubles.push_back(33.2+i);
        Pointers.push_back((Doubles.data()+i));
    }   

    
    Integers.push_back(34);
    Floats.push_back(0.67);
    Doubles.push_back(4.20);
    Pointers.push_back( (Doubles.data()+(Doubles.size()-1) ));
    for (int i = 0; i < Integers.size(); i++)
    {
        std::cout << "at " << i << " " << (Integers.at(i)) << "\n";
        
    }
    printLine("\"int\" Vector size: %d elements (%d bytes) | Capacity: %d elements (%d bytes)", Integers.size(), Integers.byte_size(), Integers.capacity(), Integers.byte_cap());

    for (int i = 0; i < Floats.size(); i++)
    {
        std::cout << "at " << i << " " << (Floats.at(i)) << "\n";
    }
    printLine("\"float\" Vector size: %d elements (%d bytes) | Capacity: %d elements (%d bytes)", Floats.size(), Floats.byte_size(), Floats.capacity(), Floats.byte_cap());
    Pointers.clear();
    for (int i = 0; i < Doubles.size(); i++)
    {
        std::cout << "at " << i << " " << (Doubles.at(i)) << "\n";
        
        Pointers.push_back(Doubles.data()+i);
        std::cout << "pointers: " << (Pointers.at(i)) << "(" << *Pointers.at(i) << ")" << "\n";
    }
    printLine("\"double\" Vector size: %d elements (%d bytes) | Capacity: %d elements (%d bytes)", Doubles.size(), Doubles.byte_size(), Doubles.capacity(), Doubles.byte_cap());
    printLine("\"double*\" Vector size: %d elements (%d bytes) | Capacity: %d elements (%d bytes)", Doubles.size(), Doubles.byte_size(), Doubles.capacity(), Doubles.byte_cap());
    
    

    
    return 0;
}
