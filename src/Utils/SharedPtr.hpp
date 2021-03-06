#ifndef __SHAREDPTR_HPP
#define __SHAREDPTR_HPP

template <class T>
class SharedPtr
{
private:
	size_t* cnt;
	T* objRef;

public:
	explicit SharedPtr();
	explicit SharedPtr(T* objRef);
	SharedPtr(const SharedPtr& other);
	SharedPtr& operator =(const SharedPtr& other);
	~SharedPtr();

public:
	T* operator->() const;

public:
	bool isNull() const;
	T* getRaw();
	const T* getRaw() const;
};


template<class T>
inline SharedPtr<T>::SharedPtr() : cnt(new size_t(1)), objRef(nullptr)
{}

template<class T>
inline SharedPtr<T>::SharedPtr(T* objRef) : cnt(new size_t(1)), objRef(objRef)
{}

template<class T>
inline SharedPtr<T>::SharedPtr(const SharedPtr<T> & other) : cnt(other.cnt), objRef(other.objRef)
{
	(*cnt)++;
}

template<class T>
inline SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr<T>& other)
{
	if (this != &other)
	{
		(*cnt)--;
		if ((*cnt) == 0)
		{
			delete cnt;
			delete objRef;
		}

		cnt = other.cnt;
		objRef = other.objRef;
		(*cnt)++;
	}

	return *this;
}

template<class T>
inline SharedPtr<T>::~SharedPtr<T>()
{
	(*cnt)--;
	if ((*cnt) == 0)
	{
		delete cnt;
		delete objRef;
	}
}

template<typename T>
T* SharedPtr<T>::operator->() const
{
	return &*objRef;
}

template<class T>
inline bool SharedPtr<T>::isNull() const
{
	return objRef==nullptr;
}

template<class T>
inline T* SharedPtr<T>::getRaw()
{
	return objRef;
}

template<class T>
inline const T* SharedPtr<T>::getRaw() const
{
	return objRef;
}

#endif // !__SHAREDPTR_HPP
