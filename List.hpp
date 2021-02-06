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
		node *_endptr;
		size_type _size;
		allocator_type _alloc;

	 public:

		explicit List(const allocator_type &alloc = Allocator())
		{
			_endptr = new node();
			_endptr->next = _endptr;
			_endptr->prev = _endptr;
			_size = 0;
			_alloc = alloc;
		}

		~List()
		{
			clear();
			delete _endptr;
		}

		/* begin end blah blah */

		iterator begin()
		{
			return iterator(_endptr->next);
		}

		iterator end()
		{
			return iterator(_endptr);
		}

		reference front()
		{
			return _endptr->next->data;
		}

		const_reference front() const
		{
			return _endptr->next->data;
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

			/* reassign old nodes */
			for (it = begin(); it != end() and n > 0; ++it, --n)
				*it = val;
			/* delete excess nodes */
			for (; it != end(); ++it)
				pop_back();
			/* create new nodes */
			for (; n > 0; --n)
				push_back(val);
		}

		void	push_front(const value_type & val)
		{
			node *tmp = _endptr->next;

			_endptr->next = new node(val);
			_endptr->next->prev = _endptr;
			tmp->prev = _endptr->next;
			_endptr->next->next = tmp;
			++_size;
		}

		void	push_back(const value_type &val)
		{
			node *to_add = new node(val);

			to_add->next = _endptr;
			to_add->prev = _endptr->prev;
			_endptr->prev = to_add;
			to_add->prev->next = to_add;
			++_size;
		}

		void	pop_back()
		{
			if (_size)
			{
				node *to_link = _endptr->prev->prev;

				delete _endptr->prev;
				_endptr->prev = to_link;
				to_link->next = _endptr;
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
