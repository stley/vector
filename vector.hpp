#include <cstdint>
#include <stdlib.h>
#include <iostream>
#include <type_traits>

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
    
    void cleanup(T* ptr, size_t len)
    {
        for (size_t i = 0; i < len; i++)
        {
            //(ptr+i)->~T();
        }
        free(ptr);
    }
    //modifiers
    bool push_back(const T& value);

    //access
    T& at(size_t index);
    T* operator[](size_t index);

    bool empty();
    size_t size();
    size_t byte_size();
    size_t max_size();
    bool reserve(size_t resize);
    size_t capacity();
    size_t byte_cap();
    bool shrink_to_fit(size_t resize);


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
            size_t new_cap = capacity_*2;
            T* new_ptr = reinterpret_cast<T*>(malloc((sizeof(T)*new_cap)));

            if (!new_ptr) return false;

            std::memcpy(new_ptr, data_pointer, (size_ * sizeof(T)));
            cleanup(data_pointer, (sizeof(T) * size_));
            
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
T* vector<T>::operator[](size_t index)
{
    if (index >= size_ )
        throw std::out_of_range("Vector index out of range");

    else return (data_pointer+index);
}

template <typename T>
bool vector<T>::empty()
{
    return (size_ == 0);
}

template <typename T>
size_t vector<T>::size()
{
    return this->size_;
}

template <typename T>
size_t vector<T>::max_size()
{
    return this->capacity_;
}

template <typename T>
size_t vector<T>::capacity()
{
    return this->capacity_;
}

template <typename T>
size_t vector<T>::byte_size()
{
    return (this->size_)*sizeof(T);
}

template <typename T>
size_t vector<T>::byte_cap()
{
    return (this->capacity_)*sizeof(T);
}










}


