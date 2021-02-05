//
// Created by user on 05.02.2021.
//

#ifndef FT_CONTAINERS_LIST_HPP
#define FT_CONTAINERS_LIST_HPP
#include "Iterator.hpp"
#include "BidirectionalIterator.hpp"
#include "DNode.hpp"
#include <memory>

namespace shitty
{

	template <class T, class Allocator = std::allocator<T> >
	class List
	{
	 public:
		typedef T value_type;
		typedef DNode<T> node;
		typedef Allocator allocator_type;
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;
		typedef typename Allocator::reference reference;
		typedef typename Allocator::const_reference const_reference;
		typedef typename Allocator::pointer pointer;
		typedef typename Allocator::const_pointer const_pointer;
		typedef shitty::BidirectionalIterator<T> iterator;
		typedef shitty::BidirectionalIterator<T, const T *, const T &> const_iterator;
		typedef shitty::ReverseIterator<iterator> reverse_iterator;
		typedef shitty::ReverseIterator<const_iterator> const_reverse_iterator;

	 private:
		node *_head;
		node *_endptr;
		size_type _size;
		allocator_type _alloc;

	 public:

		explicit List(const allocator_type &alloc = Allocator())
		{
			_head = new node();
			_endptr = _head;
			_size = 0;
			_alloc = alloc;
		}

		~List()
		{
			delete _endptr;
		}

		/* begin end blah blah */

		iterator begin()
		{
			return iterator(_head);
		}

		iterator end()
		{
			return iterator(_endptr);
		}

		reference front()
		{
			return _head->data;
		}

		const_reference front() const
		{
			return _head->data;
		}

		reference back()
		{
			return _endptr->prev->data;
		}

		const_reference back() const
		{
			return _endptr->prev->data;
		}

		/* size */

		bool	empty() const
		{
			return not _size;
		}

		size_type size() const
		{
			return _size;
		}

		size_type max_size() const
		{
			return SIZE_T_MAX / sizeof(node);
		}

		/* push pop */

		void	assign(size_type n, const value_type& val)
		{
			iterator it;

			for (it = begin(); it != end(), n > 0; ++it, --n)
			{
				it->ptr->data = val;
			}
			for (; n > 0; --n)
				push_back(val);
		}

		void	push_front(const value_type & val)
		{
			_head->prev = new node(val);
			_head->prev->next = _head;
			_head = _head->prev;
			_head->prev = _endptr;
			_endptr->next = _head;
			++_size;
		}

		void	push_back(const value_type &val)
		{
			node *to_add = new node(val);

			to_add->next = _endptr;
			if (_endptr == _head)
			{
				_head = to_add;
				_endptr->prev = to_add;
			}
			else
			{
				_endptr->prev->next = to_add;
				to_add->prev = _endptr->prev;
				_endptr->prev = to_add;
			}
			++_size;
		}

		void	pop_back()
		{
			if (_size)
			{
				node *to_link = _endptr->prev->prev;

				if (to_link)					// size > 0: "forget" last elem
					to_link->next = _endptr;
				else							// size is 0: relink head with endptr
					_head = _endptr;
				delete _endptr->prev;
				_endptr->prev = to_link;
				--_size;
			}
		}

		void clear()
		{
			while (_size)
				pop_back();
		}
	};
};

#endif //FT_CONTAINERS_LIST_HPP
