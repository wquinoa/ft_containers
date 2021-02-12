//
// Created by user on 05.02.2021.
//

#ifndef FT_CONTAINERS_BIDIRECTIONALITERATOR_HPP
#define FT_CONTAINERS_BIDIRECTIONALITERATOR_HPP
# include "Iterator.hpp"
# include "List/DNode.hpp"

namespace ft
{
	template <class T>
	struct DNode;

	template<typename T, typename Pointer = T *, typename Reference = T &>
	class BidirectionalIterator
	{
	 public:
		typedef BidirectionalIterator<T, Pointer, Reference> _self;
		typedef BidirectionalIterator<T, T*, T&>			 iterator;
		typedef BidirectionalIterator<T, const T*, const T&> const_iterator;
		typedef T											value_type;
		typedef Pointer										pointer;
		typedef Reference									reference;
		typedef size_t										size_type;
		typedef ptrdiff_t									difference_type;
		typedef	ft::bidirectional_iterator_tag			iterator_category;
		typedef DNode<value_type> *							node_pointer;

		friend class	ft::List<T>;

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

		BidirectionalIterator(const iterator &x) : ptr(x.get_ptr())
		{
		}

		node_pointer get_ptr() const
		{
			return ptr;
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

		T	&operator* ()
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
