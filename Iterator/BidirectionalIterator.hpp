//
// Created by user on 05.02.2021.
//

#ifndef FT_CONTAINERS_BIDIRECTIONALITERATOR_HPP
#define FT_CONTAINERS_BIDIRECTIONALITERATOR_HPP
# include "Iterator.hpp"
# include "DNode.hpp"

namespace shitty
{
	template <class T>
	struct DNode;

	template<typename T, typename Pointer = T *, typename Reference = T &>
	class BidirectionalIterator
	{
	 public:
		typedef T										value_type;
		typedef Pointer									pointer;
		typedef Reference								reference;
		//typedef BidirectionalIterator					biterator;
		typedef BidirectionalIterator<T, Pointer, Reference>		_self;
		typedef BidirectionalIterator<T, T *, T &>					iterator;
		typedef BidirectionalIterator<T, const T *, const T &>		const_iterator;
		typedef size_t									size_type;
		typedef ptrdiff_t								difference_type;
		typedef DNode<T>*								node_pointer;
		typedef shitty::bidirectional_iterator_tag		iterator_category;

		friend class 									shitty::List<T>;

	 protected:
		node_pointer ptr;

	 public:
		BidirectionalIterator() : ptr()
		{
		}

		~BidirectionalIterator()
		{
		}

		BidirectionalIterator(const node_pointer elem) : ptr(elem)
		{
		}

		BidirectionalIterator(const iterator &x) : ptr(x.ptr)
		{
		}

		_self &operator= (const_iterator &copy)
		{
			if (this != &copy)
				ptr = copy.ptr;
			return *this;
		}

		_self operator++ (int)
		{
			_self 	old(ptr);

			ptr = ptr->next;
			return *this;
		}

		_self &operator++ ()
		{
			ptr = ptr->next;
			return *this;
		}

		_self operator-- (int)
		{
			_self 	old(ptr);

			ptr = ptr->prev;
			return *this;
		}

		_self &operator-- ()
		{
			ptr = ptr->prev;
			return *this;
		}

		T	&operator* () const
		{
			return ptr->data;
		}

		bool operator== (const BidirectionalIterator &rhs) const
		{
			return ptr == rhs.ptr;
		}

		bool operator!= (const BidirectionalIterator &rhs) const
		{
			return !(rhs == *this);
		}
	};
}
//# include "List.hpp"
#endif //FT_CONTAINERS_BIDIRECTIONALITERATOR_HPP
