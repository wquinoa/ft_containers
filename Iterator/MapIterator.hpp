//
// Created by user on 15.02.2021.
//

#ifndef MAP_ITERATOR_HPP
# define MAP_ITERATOR_HPP
#include "Algorithm.hpp"
#include "RBTree.hpp"

namespace ft
{
	template <class T>
	struct RBNode;

	template<typename T, typename Pointer = T *, typename Reference = T &, class Compare = ft::less<T> >
	class MapIterator
	{
	 public:
		typedef MapIterator<T, Pointer, Reference, Compare> _self;
		typedef MapIterator<T, T*, T&, Compare>			 	iterator;
		typedef MapIterator<T, const T*, const T&, Compare> const_iterator;
		typedef T											value_type;
		typedef Pointer										pointer;
		typedef Reference									reference;
		typedef size_t										size_type;
		typedef ptrdiff_t									difference_type;
		typedef	ft::bidirectional_iterator_tag				iterator_category;
		typedef RBNode<value_type> *						node_pointer;

		//friend class RBTree;

	 protected:
		Compare			comp;
		node_pointer	ptr;

		bool 			compare(node_pointer a, node_pointer b)
		{ return comp(a->data->first, b->data->first); }

	 public:
		MapIterator() : ptr()
		{
		}

		~MapIterator()
		{
		}

		MapIterator(const node_pointer elem) : ptr(elem)
		{
		}

		MapIterator(const iterator &x) : ptr(x.get_ptr())
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

			operator++();
			return old;
		}

		_self &operator++ ()
		{
			if (ptr->right->right != ptr->right->left)
			{
				ptr = ptr->_right;
				if (ptr->right->right == ptr->right->left)
					return ptr;
				while (ptr->left->left != ptr->left->right)
					ptr = ptr->left;
			}
			else
			{
				if (compare(ptr, ptr->parent))
					ptr = ptr->parent;
				else
				{
					while (not compare(ptr, ptr->parent))
						ptr = ptr->parent;
					ptr = ptr->parent;
				}
			}
			return *this;
		}

		_self operator-- (int)
		{
			return *this;
		}

		_self &operator-- ()
		{
			return *this;
		}

		T	&operator* ()
		{
			return ptr->data;
		}

		bool operator== (const MapIterator &rhs) const
		{
			return ptr == rhs.ptr;
		}

		bool operator!= (const MapIterator &rhs) const
		{
			return !(rhs == *this);
		}
	};
}

#endif
