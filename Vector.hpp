//
// Created by Filipp Ewseew on 1/30/21.
//

#ifndef FT_CONTAINERS__VECTOR_HPP_
# define FT_CONTAINERS__VECTOR_HPP_
# include <iostream>
# include <memory>
# include <cmath>
# include "RandomAccessIterator.hpp"
# include "Algorithm.hpp"


namespace shitty
{
	template<class T, class Allocator = std::allocator<T> >
	class Vector
	{
	 public:
		typedef Allocator 												allocator_type;
		typedef size_t 													size_type;
		typedef T 														value_type;
		typedef value_type &											reference;
		typedef const value_type &										const_reference;
		typedef ptrdiff_t 												difference_type;
		typedef value_type *											pointer;
		typedef const value_type *										const_pointer;
		typedef shitty::RandomAccessIterator<T>							iterator;
		typedef shitty::RandomAccessIterator<T, const T *, const T &> 	const_iterator;

	 private:
		size_type		_size;
		pointer			_beginptr;
		size_type		_capacity;
		allocator_type	_alloc;

	 public:
		inline explicit Vector(allocator_type const &a = allocator_type())
		: _size(), _beginptr(), _capacity(), _alloc(a)
		{
		};

		inline explicit Vector(size_type n, value_type &val = value_type(),
			const allocator_type &a = allocator_type())
		: _size(n), _capacity(n), _alloc(a)
		{
			_beginptr = new value_type[n]();
			for (size_type i = 0; i < n; i++)
				_beginptr[i] = val;
		};

		template<class Iter>
		Vector (Iter first, Iter last,const allocator_type &alloc = allocator_type())
		: _alloc(alloc)
		{
			_capacity = shitty::distance(first, last);
			_size = _capacity;
			_beginptr = new value_type[_capacity];
			assign(first, last);
		}

		Vector(const Vector &copy)
		{
			*this = copy;
		}

		~Vector()
		{
			delete[] _beginptr;
		}

		/* iterators */

		iterator begin()
		{
			return iterator(_beginptr);
		}

		const_iterator begin() const
		{
			return const_iterator(_beginptr);
		}

		iterator end()
		{
			return iterator(_beginptr + _size);
		}

		const_iterator end() const
		{
			return const_iterator(_beginptr + _size);
		}

		/* Getters */

		size_type	size() const
		{
			return _size;
		}

		size_type	max_size() const
		{
			return _alloc.max_size();
		}

		size_type	capacity() const
		{
			return _capacity;
		}

		bool	empty() const
		{
			return (_size == 0);
		}

		/* Memory management */

//		void nearestpow(size_type &n)
//		{
//			n -= 1;
//			n = n | (n >> 1);
//			n = n | (n >> 2);
//			n = n | (n >> 4);
//			n = n | (n >> 8);
//			n = n | (n >> 16);
//			n += 1;
//		}

		void reserve(size_type n)
		{
			if (n > _capacity)
			{
				//nearestpow(n);

				_capacity = n;
				pointer tmp = new value_type[n];
				for (size_t i = 0; i < _size; ++i)
					tmp[i] = _beginptr[i];
				//::memmove(tmp, _beginptr, _size * sizeof(value_type));
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
//				if (capacity() > n)
//					_capacity = n;
			}
		}

		void clear()
		{
			_size = 0;
		}

		/* Addition - removal */

		void push_back(const value_type &n)
		{
			if (_size == _capacity)
				reserve(_capacity * 2);
			_beginptr[_size] = n;
			_size++;
		}

		void pop_back()
		{
			_size--;
		}

		template<class Iterator>
		void assign(Iterator from, Iterator to)
		{
			clear();
			for (; from != to; ++from)
				push_back(*from);
		}

		void assign(size_type n, const value_type &val)
		{
			clear();
			insert(begin(), n, val);
		}

		void insert(iterator position, size_type n, const value_type &val)
		{
/*
			difference_type to_pos = position - begin();
			difference_type to_end = _size - to_pos;
#ifdef SHITTY_DEBUG
			PRINT("copy " << to_end * sizeof(value_type) << " bytes")
			PRINT("from index: " << to_pos)
			PRINT("to index: " << to_pos + n)
			PRINT("size b4 copy is " << _size)
			PRINT("size + n is " << _size + n)
#endif
			while (_capacity < (_size + n))
				reserve(_capacity * 2);

			// copy old values to new pos
			::memmove(_beginptr + to_pos + n, _beginptr + to_pos, to_end * sizeof(value_type));
#ifdef SHITTY_DEBUG
			PRINT("copied values: ")
			for (int i = 0; i < _size; ++i)
				std::cout << _beginptr[i + to_pos + n] << " ";
			PRINT("")
			PRINT("to indices: ")
			for (int i = 0; i < _size; ++i)
				std::cout << i + to_pos + n << " ";
			PRINT("")
#endif
			// add new values to requested pos
			_size += n;
			for ( ; n > 0; --n)
				_beginptr[to_pos + n - 1] = val;
				*/

			Vector		tmp(position, end());
			iterator	it;

			_size -= end() - position;
			reserve(n);
			for (; n; --n)
				push_back(val);

			for (it = tmp.begin(); it != tmp.end(); ++it)
				push_back(*it);
		}

		iterator insert(iterator position, const value_type &val)
		{
			insert(position, 1, val);
			return (position);
		}

		iterator	erase(iterator first, iterator last)
		{
			/*
			difference_type copy_to = first - begin();
			difference_type copy_from = last - begin();
			difference_type copy_size = end() - last;

			// copy (end - last) elements to first
			::memmove(_beginptr + copy_to, _beginptr + copy_from, copy_size * sizeof(value_type));
			_size -= copy_from - copy_to;
			return last;
			*/
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

		reference		at(size_type n)
		{
			if (n >= _size)
				throw std::out_of_range("index out of range");
			return _beginptr[n];
		}

		const_reference	at(size_type n) const
		{
			if (n >= _size)
				throw std::out_of_range("index out of range");
			return _beginptr[n];
		}

		reference		operator[](size_type n)
		{
			return _beginptr[n];
		}

		const_reference	operator[](size_type n) const
		{
			return _beginptr[n];
		}

		reference		front()
		{
			return *_beginptr;
		}

		const_reference	front() const
		{
			return *_beginptr;
		}

		reference		back()
		{
			return _beginptr[_size - 1];
		}

		const_reference	back() const
		{
			return _beginptr[_size - 1];
		}

	};
}

#endif //FT_CONTAINERS__VECTOR_HPP_
