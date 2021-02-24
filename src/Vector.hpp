//
// Created by Filipp Ewseew on 1/30/21.
//

#ifndef FT_CONTAINERS__VECTOR_HPP_
# define FT_CONTAINERS__VECTOR_HPP_
# include <memory>
# include <cmath>
# include "Iterator/RandomAccessIterator.hpp"
# include "Iterator/Iterator.hpp"
# include "Algorithm.hpp"


namespace ft
{
	template<class T, class Allocator = std::allocator<T> >
	class Vector
	{
	 public:
		typedef Allocator 											allocator_type;
		typedef size_t 												size_type;
		typedef T 													value_type;
		typedef value_type &										reference;
		typedef const value_type &									const_reference;
		typedef ptrdiff_t 											difference_type;
		typedef value_type *										pointer;
		typedef const value_type *									const_pointer;
		typedef ft::RandomAccessIterator<T>							iterator;
		typedef ft::RandomAccessIterator<T, const T *, const T &> 	const_iterator;
		typedef ft::ReverseIterator<iterator>						reverse_iterator;
		typedef const reverse_iterator 								const_reverse_iterator;

	 private:
		size_type		_size;
		pointer			_beginptr;
		size_type		_capacity;
		allocator_type	_alloc;

	 public:
		inline explicit Vector(allocator_type const &a = allocator_type())
		: _size(), _beginptr(), _capacity(), _alloc(a)
		{
		}

		inline explicit Vector(size_type n, value_type &val = value_type(),
			const allocator_type &a = allocator_type())
		: _size(n), _capacity(n), _alloc(a)
		{
			_beginptr = new value_type[n]();
			for (size_type i = 0; i < n; i++)
				_beginptr[i] = val;
		}

		template<class Iter>
		Vector (Iter first, Iter last, const allocator_type &alloc = allocator_type())
		: _alloc(alloc)
		{
			_size = _capacity = 0;
			_beginptr = new value_type[0];
			while (first != last)
			{
				push_back(*first);
				++first;
			}
		}

		Vector(const Vector &copy)
		{
			*this = copy;
		}

		Vector &operator= (const Vector &copy)
		{
			if (this != &copy)
			{
				_size = copy._size;
				_capacity = copy._capacity;
				_alloc = copy._alloc;
				_beginptr = new value_type[_capacity];
				for (size_type i = 0; i < _size; ++i)
					_beginptr[i] = copy._beginptr[i];
			}
			return (*this);
		}

		~Vector()
		{
			delete[] _beginptr;
		}

		/* iterators */

		inline iterator                 begin()         { return iterator(_beginptr); }
		inline const_iterator           begin() const   { return const_iterator(_beginptr); }
		inline iterator                 end()           { return iterator(_beginptr + _size); }
        inline const_iterator           end() const     { return const_iterator(_beginptr + _size); }
        inline reverse_iterator		    rbegin()        { return reverse_iterator(_beginptr + (_size - 1)); }
        inline const_reverse_iterator	rbegin() const  { return reverse_iterator(_beginptr + (_size - 1)); }
		inline reverse_iterator		    rend()          { return reverse_iterator(_beginptr - 1); }
		inline const_reverse_iterator	rend() const    { return reverse_iterator(_beginptr - 1); }

		/* Getters */

		inline size_type	size() const        { return _size; }
		inline size_type	max_size() const    { return _alloc.max_size(); }
		inline size_type	capacity() const    { return _capacity; }
		inline bool	        empty() const       { return (_size == 0); }

		/* Memory management */

		void        reserve(size_type n)
		{
			if (n > _capacity)
			{
				_capacity = n;
				pointer tmp = new value_type[n];
				for (size_t i = 0; i < _size; ++i)
					tmp[i] = _beginptr[i];
				delete[] _beginptr;
				_beginptr = tmp;
			}
			else if (n == 0 && n == _capacity)
				reserve(1);
		}

		void		resize(size_type n, value_type val = value_type())
		{
			if (_size > n)
				_size = n;
			else
			{
				reserve(n);
				insert(end(), n - _size, val);
			}
		}

		inline void clear()
		{
			_size = 0;
		}

		/* Addition - removal */

		void        push_back(const value_type &n)
		{
			if (_size == _capacity)
				reserve(_capacity * 2);
			_beginptr[_size] = n;
			_size++;
		}

		inline void pop_back()
		{
			_size--;
		}

		template <class InputIt>
		void        assign(InputIt from, InputIt to,
			  typename ft::has_iterator_category<InputIt>::value * = false)
		{
			clear();
			while (from != to)
			{
				push_back(*from);
				++from;
			}
		}

		void		assign(size_type n, const value_type& val)
		{
			clear();
			insert(begin(), n, val);
		}

		void        insert(iterator position, size_type n, const value_type &val)
		{
			Vector		tmp(position, end());
			iterator	it;

			_size -= end() - position;
			reserve(n);
			for (; n; --n)
				push_back(val);

			for (it = tmp.begin(); it != tmp.end(); ++it)
				push_back(*it);
		}

		iterator    insert(iterator position, const value_type &val)
		{
			insert(position, 1, val);
			return (position);
		}

		iterator	erase(iterator first, iterator last)
		{
			iterator ret = last;

			for ( ; last != end(); ++first, ++last)
				*first = *last;
			_size -= (last - first);
			return ret;
		}

		iterator	erase(iterator position)
		{
			return erase(position, position + 1);
		}

		/* Access */

		inline reference	    at(size_type n)
		{
			if (n >= _size)
				throw std::out_of_range("index out of range");
			return _beginptr[n];
		}

		inline const_reference	at(size_type n) const
		{
			if (n >= _size)
				throw std::out_of_range("index out of range");
			return _beginptr[n];
		}

		void    swap(Vector<T> &other)
        {
		    ft::swap(_size, other._size);
		    ft::swap(_beginptr, other._beginptr);
		    ft::swap(_capacity, other._capacity);
		    ft::swap(_alloc, other._alloc);
        }

        inline reference		operator[](size_type n)         { return _beginptr[n]; }
		inline const_reference	operator[](size_type n) const   { return _beginptr[n]; }
		inline reference		front()                         { return *_beginptr; }
		inline const_reference	front() const                   { return *_beginptr; }
		inline reference		back()                          { return _beginptr[_size - 1]; }
		inline const_reference	back() const                    { return _beginptr[_size - 1]; }

		/* Relational */

        friend bool operator==(const Vector &lhs, const Vector &rhs)
        {
            return ft::lexicographical_equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
        }

        friend bool operator< (const Vector &lhs, const Vector &rhs)
        {
            return ft::lexicographical_less(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
        }

        friend bool operator> (const Vector &lhs, const Vector &rhs) { return rhs < lhs; }
        friend bool operator<=(const Vector &lhs, const Vector &rhs) { return not (rhs < lhs); }
        friend bool operator>=(const Vector &lhs, const Vector &rhs) { return not (lhs < rhs); }
        friend bool operator!=(const Vector &lhs, const Vector &rhs) { return not (rhs == lhs); }
	};

    template< class T, class Alloc >
    void swap( ft::Vector<T,Alloc>& lhs, ft::Vector<T,Alloc>& rhs ) { lhs.swap(rhs); }
}

#endif //FT_CONTAINERS__VECTOR_HPP_
