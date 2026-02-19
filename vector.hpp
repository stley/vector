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

    bool grow();
public:
    vector()
    {
        //static_assert(std::is_trivially_copyable_v<T>, "Vector for non trivial instances is not supported.");
        this->data_pointer = nullptr;
        this->size_ = 0;
        this->capacity_ = 0;
    }
    ~vector()
    {
        for (size_t i = 0; i < size_; i++)
        {
            (data_pointer+i)->~T();
        }
        ::operator delete(data_pointer);
    }
    
    //Element Access
    T& at(size_t index);
    T& operator[](size_t index);
    const T& at(size_t index) const;
    const T& operator[](size_t index) const;
    T& front() { return *data_pointer; }
    T& back() 
    {
        if ( size_ < 1) return *data_pointer;
        return *(data_pointer + (size_-1));
    }
    T* data() { return data_pointer; }
    
    //Capacity
    bool empty() const { return (size_ == 0); }
    size_t size() const { return this->size_; }
    size_t byte_size() const { return (this->size_)*sizeof(T); }
    size_t max_size() const { return return SIZE_MAX / sizeof(T); }
    size_t capacity() const { return this->capacity_; }
    size_t byte_cap() const { return (this->capacity_)*(sizeof(T)); }
    
    
    //Modifiers
    void clear();

    bool push_back(const T& value);

    void pop_back();
    
    bool resize(size_t newsize);

    bool reserve(size_t to_reserve);
};




template <typename T>
bool vector<T>::grow()
{    
    std::cout << "Grow called\n";
    size_t new_cap = capacity_ + (capacity_/2);
    if(!capacity_) new_cap = 2;
    
    T* new_ptr = static_cast<T*>(::operator new( (sizeof(T)*new_cap) ));

    if (!new_ptr) return false;

    for(size_t i = 0; i < size_; i++)
    {
        new (new_ptr + i) T(std::move( *(data_pointer + i) ));
    }

    for(size_t i = 0; i < size_; i++)
    {
        data_pointer[i].~T();
    }

    ::operator delete(data_pointer);

    data_pointer = new_ptr;
    capacity_ = new_cap;
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
void vector<T>::clear()
{
    for(size_t i = 0; i < size_; i++)
    {
        data_pointer[i].~T();
    }

    this->size_ = 0;
}

template <typename T>
bool vector<T>::push_back(const T& value)
{

    if(size_ == capacity_)
    {
        if (!this->grow())
            return false;

    }
    new (data_pointer + size_) T(value);
    size_++;
    return true;
}

template <typename T>
void vector<T>::pop_back()
{
    if(size_ > 0)
    {

        data_pointer[size_-1].~T();
        size_--;
    }
}

template <typename T>
bool vector<T>::resize(size_t newsize)
{
    if (!data_pointer)
    {
        if (newsize == 0)
            return true;
        data_pointer = static_cast<T*>( ::operator new (sizeof(T)*newsize));
        if (!data_pointer) return false;
        capacity_ = newsize;

        for (size_t i = 0; i < newsize; ++i)
        {
            new (data_pointer + i) T();
        }

        size_ = newsize;
        return true;
    }

    size_t old_size = size_;

    if (newsize == 0)
    {
        this->clear();
        return true;
    }
    
    if (newsize <= size_)
    {
        for(size_t i = newsize; i < size_; i++)
        {
            data_pointer[i].~T();
        }
        size_ = newsize;
        return true;
    }

    
    if (newsize <= capacity_)
    {
        for(size_t i = old_size; i < newsize; i++)
        {
            new (data_pointer + i) T();
        }
    }

    else
    {
        T* reallocatedPointer = static_cast<T*>( ::operator new ( (sizeof(T) * newsize)) );

        if(!reallocatedPointer)
            return false;

        

        for(size_t i = 0; i < size_; i++)
        {
            new (reallocatedPointer + i) T(std::move( *(data_pointer + i) ));
        }

        for(size_t i = 0; i < old_size; i++)
        {
            data_pointer[i].~T();
        }

        for (size_t i = old_size; i < newsize; ++i)
        {
            new (reallocatedPointer + i) T();
        }

        ::operator delete(data_pointer);

        data_pointer = reallocatedPointer;
        capacity_= newsize;
    }
    size_ = newsize;
    return true;
}

template <typename T>
bool vector<T>::reserve(size_t to_reserve)
{
    if (!data_pointer)
    {
        data_pointer = static_cast<T*>( ::operator new(sizeof(T)*to_reserve) );
        if (!data_pointer) return false;
        capacity_ = to_reserve;
        return true;
    }

    if (capacity_ >= to_reserve)
        return true;

    T* reallocatedPointer = static_cast<T*>( ::operator new( (sizeof(T)*to_reserve)) );

    for(size_t i = 0; i < size_; i++)
    {
        new (reallocatedPointer + i) T(std::move( *(data_pointer + i) ));
    }
    for(size_t i = 0; i < size_; i++)
    {
        data_pointer[i].~T();
    }

    if (!reallocatedPointer)
        return false;

    ::operator delete(data_pointer);

    data_pointer = reallocatedPointer;
    capacity_ = to_reserve;
    return true;
}


}
