#ifndef __PAIR_HPP
#define __PAIR_HPP

template <class T1, class T2>
struct Pair
{
	T1 first;
	T2 second;

	Pair();
	Pair(const T1& first, const T2& second);
};

template <class T1, class T2>
inline Pair<T1, T2>::Pair()
{}

template <class T1, class T2>
inline Pair<T1, T2>::Pair(const T1 & first, const T2 & second) : first(first), second(second)
{}

template<class T1, class T2>
bool operator==(const Pair<T1, T2>& lhs, const Pair<T1, T2>& rhs)
{
	return (lhs.first == rhs.first && lhs.second == rhs.second);
}

#endif
