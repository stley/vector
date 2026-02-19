#include <iostream>
#include "vector.hpp"
#include <cstdarg>

berkeley::vector<int> Integers;
berkeley::vector<float> Floats;
berkeley::vector<double> Doubles;
berkeley::vector<double*> Pointers;

class Person
{
public:
    Person(std::string name, int age, bool isCool) :
    name_(name),
    age_(age),
    isCool_(isCool)
    {
    }

    std::string name_;
    int age_ = 0;
    bool isCool_ = true;
    
};


struct DataTypes
{
    std::string TypeName = "nil";
    size_t byte_size = 0;
};

berkeley::vector<Person> People;

berkeley::vector<DataTypes> Types;

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

    Integers.resize(5);
    Floats.resize(5);
    Doubles.resize(5);
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
    
    
    printLine("Object testing");
    
    People.push_back(Person("Berkeley", 19, true));
    People.push_back(Person("Lulo", 20, true));
    People.push_back(Person("Messi", 38, true));


    for(size_t i = 0; i < People.size(); i++)
    {
        printLine("At index %d: My name is %s, I'm %d years old and %s", i, (People.at(i)).name_.c_str(), (People.at(i)).age_, ( ( People.at(i) ).isCool_) ? "I'm cool :)" : "I'm not cool :(");
    }

    printLine("\"Person\" Vector size: %d elements (%d bytes) | Capacity: %d elements (%d bytes)", People.size(), People.byte_size(), People.capacity(), People.byte_cap());

    DataTypes Type1;
    DataTypes Type2;
    DataTypes Type3;
    DataTypes Type4;

    Type1.TypeName = "Integer";
    Type1.byte_size = sizeof(int);
    Type2.TypeName = "Char";
    Type2.byte_size = sizeof(char);
    Type3.TypeName = "Double";
    Type3.byte_size = sizeof(double);

    Types.push_back(Type1);
    Types.push_back(Type2);
    Types.push_back(Type3);
    Types.push_back(Type4);

    printLine("Data Types:");
    for(size_t i = 0; i < Types.size(); i++)
    {
        printLine("%s - Bytes: %d", (Types.at(i)).TypeName.c_str(), (Types.at(i)).byte_size);
    }

    return 0;
}
