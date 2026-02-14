#include <cstdint>
#include <stdlib.h>
#include <iostream>
#include <type_traits>

//std::vector reimplementation, references from cppreference.com

namespace berkeley
{
    
    
    
template <typename T> class vector
{
private:
    T* data_pointer;
    size_t size_;
    size_t capacity_;


public:
    vector()
    {
        static_assert(std::is_trivially_copyable_v<T>, "Vector for non trivial instances is not supported.");
        this->data_pointer = nullptr;
        this->size_ = 0;
        this->capacity_ = 0;
    }
    ~vector()
    {
        for (size_t i = 0; i < size_; i++)
        {
            //(data_pointer+i)->~T();
        }
        free(data_pointer);
    }
    
    //Element Access
    T& at(size_t index);
    T& operator[](size_t index);
    const T& at(size_t index) const;
    const T& operator[](size_t index) const;
    T& front() { return data_pointer; }
    T& back() { return (data_pointer + size_); }
    T* data() { return data_pointer; }
    
    //Capacity
    bool empty() const { return (size_ == 0); }
    size_t size() const { return this->size_; }
    size_t byte_size() const { return (this->size_)*sizeof(T); }
    size_t max_size() const { return this->capacity_; }
    size_t capacity() const { return this->capacity_; }
    size_t byte_cap() const { return (this->capacity_)*(sizeof(T)); }
    
    
    //Modifiers
    bool clear();
    bool insert();
    bool push_back(const T& value);

    bool reserve(size_t to_reserve);

    bool resize(size_t newsize);
};


template <typename T>
bool vector<T>::push_back(const T& value)
{
    if (!data_pointer)
    {
        capacity_ = 2;
        data_pointer = reinterpret_cast<T*>(malloc(sizeof(T)*capacity_));
        if (!data_pointer) return false;
        
        
    }
    else
    {
        if (size_ == capacity_)
        {
            size_t new_cap = capacity_ + (capacity_/2);
            T* new_ptr = reinterpret_cast<T*>(realloc(data_pointer, (sizeof(T)*new_cap) ));

            if (!new_ptr)
                return false;
            
            capacity_ = new_cap;
            data_pointer = new_ptr;
        }

    }

    new (data_pointer + size_) T(value);
    size_++;
    return true;
}


template <typename T>
T& vector<T>::at(size_t index)
{
    if (index >= size_)
        throw std::out_of_range("Vector index out of range");
    
    else return *(data_pointer+index);
}

template <typename T>
const T& vector<T>::at(size_t index) const
{
    if (index >= size_)
        throw std::out_of_range("Vector index out of range");
    
    else return *(data_pointer+index);
}

template <typename T>
T& vector<T>::operator[](size_t index)
{
    return *(data_pointer+index);
}

template <typename T>
const T& vector<T>::operator[](size_t index) const
{
    return *(data_pointer+index);
}

template <typename T>
bool vector<T>::reserve(size_t to_reserve)
{
    if (!data_pointer)
    {
        data_pointer = reinterpret_cast<T*>(malloc(sizeof(T)*to_reserve));
        if (!data_pointer) return false;
        capacity_ = to_reserve;
        return true;
    }

    size_t new_cap = capacity_+to_reserve;

    T* reallocatedPointer = reinterpret_cast<T*>(realloc(data_pointer, (sizeof(T)*new_cap)));
    if(!reallocatedPointer) return false;

    data_pointer = reallocatedPointer;
    capacity_ = new_cap;
    return true;
}

template <typename T>
bool vector<T>::resize(size_t newsize)
{
    if(!data_pointer)
    {
        data_pointer = reinterpret_cast<T*>(malloc(sizeof(T)*newsize));
        if (!data_pointer) return false;
        capacity_ = newsize;
        return true;
    }
    T* reallocatedPointer = reinterpret_cast<T*>(realloc(data_pointer, (sizeof(T)*newsize)));
    if(!reallocatedPointer) return false;

    data_pointer = reallocatedPointer;
    if(newsize < size_)
        capacity_ = newsize;

    size_ = newsize;

    return true;
}


}


