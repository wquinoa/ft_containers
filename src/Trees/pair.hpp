//
// Created by user on 21.02.2021.
//

#ifndef FT_CONTAINERS_PAIR_HPP
#define FT_CONTAINERS_PAIR_HPP

namespace ft
{
	template<class T1, class T2>
	struct pair
	{
		typedef T1 first_type;
		typedef T2 second_type;

		first_type first;
		second_type second;

		pair() : first(), second()
		{
		}

		template<class U, class V>
		pair(const pair<U, V> &copy) : first(copy.first), second(copy.second)
		{
		}

		template<class U, class V>
		pair(const std::pair<U, V> &copy) : first(copy.first), second(copy.second)
		{
		}

		pair(const first_type &a, const second_type &b) : first(a), second(b) {}

		inline pair &operator=(const pair &copy)
		{
			if (this != &copy)
			{
				first = copy.first;
				second = copy.second;
			}
			return *this;
		}
	};

	template<class T1, class T2>
	inline bool operator==(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{
		return (lhs.first == rhs.first and lhs.second == rhs.second);
	}

	template<class T1, class T2>
	inline bool operator<(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs)
	{
		return (lhs.first < rhs.first or (not (rhs.first < lhs.first) and lhs.second < rhs.second));
	}

	template<class T1, class T2>
	inline bool operator!=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) { return not (lhs == rhs); }

	template<class T1, class T2>
	inline bool operator>(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) { return (rhs < lhs); }

	template<class T1, class T2>
	inline bool operator<=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) { return not (rhs < lhs); }

	template<class T1, class T2>
	inline bool operator>=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) { return not (lhs < rhs); }

}

#endif //FT_CONTAINERS_PAIR_HPP
