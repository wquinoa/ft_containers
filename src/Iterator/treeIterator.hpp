//
// Created by user on 21.02.2021.
//

#ifndef FT_CONTAINERS_TREEITERATOR_HPP
#define FT_CONTAINERS_TREEITERATOR_HPP

#include "Iterator.hpp"
#include "RBNode.hpp"

namespace ft
{

	template < typename T, typename Pointer, typename Reference, class C >
	class treeIterator
	{
	 public:
		typedef treeIterator<T, Pointer, Reference, C>	this_type;
		typedef treeIterator<T,	T*, T&, C>				iterator;
		typedef treeIterator<T, const T*, const T&, C>	const_iterator;
		typedef Pointer									pointer;
		typedef Reference								reference;
		typedef RBNode<T, C> *							node_pointer;
		typedef ptrdiff_t 								difference_type;
		typedef T 										value_type;
		typedef std::bidirectional_iterator_tag			iterator_category;

		node_pointer	ptr;
	 public:

		treeIterator() : ptr()
		{
		}

		treeIterator(const node_pointer node) : ptr(node)
		{
		}

		treeIterator(const iterator &x) : ptr(const_cast<node_pointer>(x.ptr))
		{
		}

		this_type&	operator=(const const_iterator &copy)
		{
			ptr = copy.ptr;
			return *this;
		}

		virtual ~treeIterator()
		{
		}

		node_pointer 	get_ptr() const
		{
			return ptr;
		}

		treeIterator	operator++(int)
		{
			treeIterator	out(ptr);

			ptr = ptr->nextn();
			return out;
		}

		treeIterator&	operator++()
		{
			ptr = ptr->nextn();
			return *this;
		}

		treeIterator	operator--(int)
		{
			treeIterator	out(ptr);

			ptr = ptr->prevn();
			return out;
		}

		treeIterator&	operator--()
		{
			ptr = ptr->prevn();
			return *this;
		}

		reference	operator*() { return ptr->data; }
		pointer		operator->() { return (&(ptr->data)); }

		template<typename T2, typename P, typename R, class C2>
		friend inline bool operator==(const this_type &lhs, const treeIterator<T2, P, R, C2> &rhs)
		{ return (lhs.ptr == rhs.ptr); }

		template<typename T2, typename P, typename R, class C2>
		friend inline bool operator!=(const this_type &lhs, const treeIterator<T2, P, R, C2> &rhs)
		{ return !(lhs == rhs); }
	};

}

#endif //FT_CONTAINERS_TREEITERATOR_HPP
