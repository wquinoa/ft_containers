//
// Created by user on 04.02.2021.
//

#ifndef FT_CONTAINERS_ALGORITHM_HPP
#define FT_CONTAINERS_ALGORITHM_HPP

namespace shitty
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

	template<class ForwardIt, class T>
	void fill(ForwardIt first, ForwardIt last, const T& value)
	{
		for (; first != last; ++first)
			*first = value;
	}

	template<class ForwardIt, class T>
	void copy(ForwardIt first, ForwardIt last, const T& value)
	{
		for (; first != last; ++first) {
			*first = value;
		}
	}

	template<class InputIt, class OutputIt>
	OutputIt copy(InputIt first, InputIt last, OutputIt d_first)
	{
		while (first != last)
			*d_first++ = *first++;
		return d_first;
	}

	template<class InputIt>
	InputIt copy(InputIt first, InputIt last, InputIt d_first)
	{
		while (first != last)
			*d_first++ = *first++;
		return d_first;
	}
}


#endif //FT_CONTAINERS_ALGORITHM_HPP
