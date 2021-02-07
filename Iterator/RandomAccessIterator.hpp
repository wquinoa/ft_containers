//
// Created by user on 05.02.2021.
//

#ifndef FT_CONTAINERS_RANDOMACCESSITERATOR_HPP
#define FT_CONTAINERS_RANDOMACCESSITERATOR_HPP

# include "Iterator.hpp"
# include <memory>
# include <cstddef>

namespace shitty
{

	template < typename T, typename Pointer = T*, typename Reference = T& >
	class RandomAccessIterator
	{
	 public:
		typedef RandomAccessIterator<T, Pointer, Reference> _self;
		typedef RandomAccessIterator<T, T*, T&>				iterator;
		typedef RandomAccessIterator<T, const T*, const T&>	const_iterator;
		typedef T											value_type;
		typedef Pointer										pointer;
		typedef Reference									reference;
		typedef size_t										size_type;
		typedef ptrdiff_t									difference_type;
		typedef	shitty::random_access_iterator_tag			iterator_category;

	 protected:
		pointer	ptr;
	 public:

		RandomAccessIterator() : ptr()
		{
		}

		RandomAccessIterator(const pointer elem) : ptr(elem)
		{
		}

		RandomAccessIterator(const iterator& copy) : ptr(const_cast<pointer>(copy.ptr))
		{
		}

		virtual ~RandomAccessIterator()
		{
		}

		_self&	operator= (const iterator& copy)
		{
			this->ptr = copy.ptr;
			return *this;
		}

		_self	operator++ (int)
		{
			_self old(*this);
			++ptr;
			return old;
		}

		_self&	operator++ ()
		{
			++ptr;
			return *this;
		}

		_self	operator+ (difference_type n) const
		{
			_self old(*this);
			old.ptr += n;
			return old;
		}

		_self&	operator+= (difference_type n)
		{
			ptr += n;
			return *this;
		}

		_self	operator-- (int)
		{
			_self old(*this);
			--ptr;
			return old;
		}

		_self&	operator-- ()
		{
			--ptr;
			return *this;
		}

		difference_type	operator- (RandomAccessIterator it) const
		{
			return ptr - it.ptr;
		}

		_self	operator- (difference_type n) const
		{
			_self out(*this);
			out -= n;
			return out;
		}

		_self&	operator-= (difference_type n)
		{
			this->ptr -= n;
			return *this;
		}

		reference	operator* () const
		{
			return *ptr;
		}

		pointer		operator-> ()
		{
			return *&ptr;
		}

		template<typename T2, typename P, typename R, class C>
		friend inline bool operator!=(const _self& lhs, const RandomAccessIterator<T2, P, R, C>& rhs)
		{
			return lhs.ptr != rhs.ptr;
		}

		template<typename T2, typename P, typename R, class C>
		friend inline bool operator>(const _self& lhs, const RandomAccessIterator<T2, P, R, C>& rhs)
		{
			return (rhs.ptr > lhs.ptr);
		}
	};
}

#endif
