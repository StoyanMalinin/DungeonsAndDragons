#ifndef __VECTOR_HPP
#define __VECTOR_HPP

#include "RandomGenerator.h"

template <class T>
class Vector
{
    enum{MIN_CAPACITY = 8};

private:
    T* data;
    size_t capacity, len;

private:
    void deleteDynamic();
    void deepCopyFromOther(const Vector& other);

public:
    Vector();
    Vector(size_t len);
    Vector(const Vector& other);
    Vector& operator=(const Vector& other);
    ~Vector();

    size_t getCapacity() const;
    size_t getLen() const;
    const T* getData() const;

public:
    void pushBack(T item);
    void pushFront(T item);
    void popFront();
    void popBack();
    T& operator[](size_t ind);
    const T& operator[](size_t ind) const;
    void insert(size_t ind, const T& x);
    void erase(size_t ind);

private:
    static bool isArrayTooLarge(size_t capacity, size_t len);
    bool isArrayTooLarge() const;
    static bool isArrayTooSmall(size_t capacity, size_t len);
    bool isArrayTooSmall() const;
    void resizeIfNecessary();
    static size_t getCapacityFromLen(size_t len);

public:
    void randomShuffle(RandomGenerator& rnd);
};

template<class T>
inline void Vector<T>::deleteDynamic()
{
    if (data != nullptr)
        delete[] data;
}

template<class T>
inline void Vector<T>::deepCopyFromOther(const Vector& other)
{
    len = other.len;
    capacity = other.capacity;
    data = new T[other.capacity];
    for (size_t i = 0; i < capacity; i++) data[i] = other.data[i];
}

template<class T>
inline Vector<T>::Vector() : capacity(Vector::MIN_CAPACITY), len(0), data(new T[Vector::MIN_CAPACITY])
{}

template<class T>
inline Vector<T>::Vector(size_t len)
{
    this->len = len;
    this->capacity = getCapacityFromLen(this->len);
    this->data = new T[this->capacity];
}

template<class T>
inline Vector<T>::Vector(const Vector& other)
{
    deepCopyFromOther(other);
}

template<class T>
inline Vector<T>& Vector<T>::operator=(const Vector& other)
{
    if (this != &other)
    {
        deleteDynamic();
        deepCopyFromOther(other);
    }

    return *this;
}

template<class T>
inline Vector<T>::~Vector()
{
    deleteDynamic();
}

template<class T>
inline size_t Vector<T>::getCapacity() const
{
    return capacity;
}

template<class T>
inline size_t Vector<T>::getLen() const
{
    return len;
}

template<class T>
inline const T* Vector<T>::getData() const
{
    return data;
}

template<class T>
inline void Vector<T>::pushBack(T item)
{
    insert(len, item);
}

template<class T>
inline void Vector<T>::pushFront(T item)
{
    insert(0, item);
}

template<class T>
inline void Vector<T>::popFront()
{
    if (len > 0) erase(0);
}

template<class T>
inline void Vector<T>::popBack()
{
    if (len > 0) erase(len - 1);
}

template<class T>
inline T& Vector<T>::operator[](size_t ind)
{
    return data[ind];
}

template<class T>
inline const T& Vector<T>::operator[](size_t ind) const
{
    return data[ind];
}

template<class T>
inline void Vector<T>::insert(size_t ind, const T& x)
{
    if (ind > len) return;
    for (size_t i = len; i >= ind+1; i--) std::swap(data[i], data[i - 1]);

    len++;
    data[ind] = x;

    resizeIfNecessary();
}

template<class T>
inline void Vector<T>::erase(size_t ind)
{
    if (ind >= len) return;
    for (size_t i = ind; i + 1 < len; i++) std::swap(data[i], data[i + 1]);
    
    len--;
    resizeIfNecessary();
}

template<class T>
bool Vector<T>::isArrayTooLarge(size_t capacity, size_t len)
{
    return (capacity > MIN_CAPACITY && 0.25 * capacity >= len);
}

template<class T>
bool Vector<T>::isArrayTooLarge() const
{
    return isArrayTooLarge(capacity, len);
}

template<class T>
bool Vector<T>::isArrayTooSmall(size_t capacity, size_t len)
{
    return (capacity < MIN_CAPACITY || 0.75 * capacity <= len);
}

template<class T>
bool Vector<T>::isArrayTooSmall() const
{
    return isArrayTooSmall(capacity, len);
}

template<class T>
inline void Vector<T>::resizeIfNecessary()
{
    if (isArrayTooLarge() == true)
    {
        capacity /= 2;
        T* newData = new T[capacity];
        if (data != nullptr) memcpy(newData, data, len * sizeof(T));

        if (data != nullptr) delete[] data;
        data = newData;
    }
    else if (isArrayTooSmall() == true)
    {
        capacity *= 2;
        T* newData = new T[capacity];
        if (data != nullptr) memcpy(newData, data, len * sizeof(T));

        if (data != nullptr) delete[] data;
        data = newData;
    }
}

template<class T>
inline size_t Vector<T>::getCapacityFromLen(size_t len)
{
    size_t cap = 1;
    while (cap <= len) cap *= 2;

    if (isArrayTooSmall(cap, len) == true) cap *= 2;
    return cap;
}

template<class T>
inline void Vector<T>::randomShuffle(RandomGenerator& rnd)
{
    for (size_t i = 1; i < len; i++)
        std::swap(data[i], data[rnd.randIntInRange(0, i)]);
}

#endif