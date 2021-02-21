//
// Created by user on 04.02.2021.
//

#ifndef FT_CONTAINERS_ALGORITHM_HPP
# define FT_CONTAINERS_ALGORITHM_HPP
# include "Iterator.hpp"

namespace ft
{
	template<typename T>
	struct less
	{
		bool	operator()(const T &x, const T &y) const
		{
			return (x < y);
		}
	};

	template<typename Iterator>
	ptrdiff_t	distance(Iterator first, Iterator last)
	{
		ptrdiff_t distance = 0;
		while (first != last)
		{
			++distance;
			++first;
		}
		return distance;
	}

	template <class InputIterator, class Distance>
	void		advance(InputIterator& it, Distance n)
	{
		if (n > 0)
			while (n--)
				++it;
		else
			while (n++)
				--it;
	}

	template<typename T>
	void		swap(T& a, T& b)
	{
		T tmp = a;
		a = b;
		b = tmp;
	}

	template<class T>
	const T&	min(const T& a, const T& b)
	{
		return (a < b ? a : b);
	}

	template<class T>
	const T&	max(const T& a, const T& b)
	{
		return (a > b ? a : b);
	}

	template <typename _InputIt1, typename _InputIt2>
	bool lexicographical_equal(_InputIt1 begin1, _InputIt1 end1, _InputIt2 begin2, _InputIt2 end2)
	{
		for ( ; begin1 != end1; ++begin1, ++begin2)
		{
			if (*begin1 != *begin2)
				return (false);
		}
		(void)end2;
		return (true);
	}

	template <typename _InputIt1, typename _InputIt2>
	bool lexicographical_less(_InputIt1 begin1, _InputIt1 end1, _InputIt2 begin2, _InputIt2 end2)
	{
		for ( ; begin1 != end1; ++begin1, ++begin2)
		{
			if (begin2 == end2 or *begin1 > *begin2)
				break ;
			if (*begin1 < *begin2)
				return (true);
		}
		return (false);
	}

}


#endif //FT_CONTAINERS_ALGORITHM_HPP
