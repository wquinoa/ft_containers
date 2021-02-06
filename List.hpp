//
// Created by user on 05.02.2021.
//

#ifndef FT_CONTAINERS_LIST_HPP
# define FT_CONTAINERS_LIST_HPP
# include "Iterator.hpp"

# include "DNode.hpp"
# include <memory>



namespace shitty
{
	template<typename T, typename Pointer, typename Reference>
	class BidirectionalIterator;

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
		typedef shitty::BidirectionalIterator<T, T *, T &> iterator;
		typedef shitty::BidirectionalIterator<T, const T *, const T &> const_iterator;
		typedef shitty::ReverseIterator<iterator> reverse_iterator;
		typedef shitty::ReverseIterator<const_iterator> const_reverse_iterator;

	 private:
		node *_endptr;
		size_type _size;
		allocator_type _alloc;

		void	createEndNode()
		{
			_endptr = new node();
			_endptr->next = _endptr;
			_endptr->prev = _endptr;
		}

	 public:

		explicit List(const allocator_type &alloc = Allocator()) : _size(), _alloc(alloc)
		{
			createEndNode();
		}

		explicit List(size_type n, const value_type &val = value_type(),
				const allocator_type &alloc = allocator_type()) : _size(), _alloc(alloc)
		{
			createEndNode();
			assign(n, val);
		}

		template<class InputIt>
		List(InputIt first, InputIt last, const allocator_type &alloc = allocator_type(),
				typename shitty::has_iterator_typedefs<InputIt>::value * = nullptr) : _alloc(alloc)
		{
			createEndNode();
			assign(first, last);
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

		reverse_iterator rbegin()
		{
			return reverse_iterator(_endptr->prev);
		}

		reverse_iterator rend()
		{
			return reverse_iterator(_endptr);
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

		/* erase assign etc */

		template< class InputIt >
		void insert(iterator pos, InputIt first, InputIt last,
			  typename shitty::has_iterator_typedefs<InputIt>::value = nullptr)
		{
			while (first != last)
				insert(pos, *first++);
		}

		iterator 	insert(iterator pos, const value_type &val)
		{
			node *elem = new node(val);

			/*
			 * 	   elem
			 *   /	    \
			 *  pos- - -pos->next;
			 */

			elem->prev = pos.ptr;
			elem->next = pos.ptr->next;
			elem->next->prev = elem;
			elem->prev->next = elem;
			++_size;
			return (++pos);
		}

		void 		insert(iterator pos, size_type n, const value_type &val)
		{
			for ( ; n > 0; --n)
				insert(pos, val);
		}

		iterator 	erase(iterator first, iterator last)
		{
			while (first != last)
				erase(first++);
			return first;
		}

		iterator 	erase(iterator pos)
		{
			/* link next and prev */
			pos.ptr->next->prev = pos.ptr->prev;
			pos.ptr->prev->next = pos.ptr->next;

			delete pos.ptr;
			--_size;
			return ++pos;
		}

		template <class InputIt>
		void assign(InputIt first, InputIt last,
			  typename shitty::has_iterator_typedefs<InputIt>::value = 0)
		{
			iterator b = begin();
			iterator e = end();

			/* reassign old nodes */
			for (; first != last and b != e; ++b, ++first)
				*b = *first;
			/* delete excess nodes */
			erase(b, e);
			/* add new nodes */
			insert(first, last);
		}


		void		assign(size_type n, const value_type& val)
		{
			iterator b = begin();
			iterator e = end();

			/* reassign old nodes */
			for (; b != e and n > 0; ++b, --n)
				*b = val;
			/* delete excess nodes */
			for (; b != e; ++b)
				b = erase(b);
			/* create new nodes */
			for (; n > 0; --n)
				push_back(val);
		}

		void	resize(size_type n, value_type val = value_type())
		{
			while (_size > n)
				pop_back();
			while (_size < n)
				push_back(val);
		}

		/* push pop */

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

		void	pop_front()
		{
			if (_size)
			{
				node *to_link = _endptr->next->next;

				delete _endptr->next;
				_endptr->next = to_link;
				to_link->prev = _endptr;
				--_size;
			}
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

		void	clear()
		{
			while (_size)
				pop_back();
		}

		/*
		 *	Operations

		 	merge

			splice

			remove

			remove_if

			reverse

			unique

			sort

			sorts the elements
		 */

		void splitInTwo(node* head, node** a, node** b)
		{
			node* fast;
			node* slow;
			slow = head;
			fast = head->next;

			/* Advance 'fast' two nodes, and advance 'slow' one node */
			while (fast != _endptr)
			{
				fast = fast->next;
				if (fast != _endptr)
				{
					slow = slow->next;
					fast = fast->next;
				}
			}

			/* 'slow' is before the midpoint in the list, so split it in two
			at that point. */
			*a = head;
			*b = slow->next;
			slow->next = _endptr;
		}

		node *merge(node *a, node *b)
		{
			/* Base cases */
			if (a == _endptr)
				return (b);
			if (b == _endptr)
				return (a);

			node *result;

			/* Pick either a or b, and recur */
			if (a->data < b->data)
			{
				result = a;
				result->next = merge(a->next, b);
				result->next->prev = result;
			}
			else
			{
				result = b;
				result->next = merge(a, b->next);
				result->next->prev = b;
			}
			return (result);
		}

		void merge_sort(node **lst)
		{
			if (*lst == _endptr or (*lst)->next == _endptr)
				return ;

			node *a;
			node *b;

			splitInTwo(*lst, &a, &b);
			merge_sort(&a);
			merge_sort(&b);

			*lst = merge(a, b);
			(*lst)->prev = _endptr;
		}

		void	splice(iterator pos, List &other)
		{
			if (not other.empty())
			{
				node *old_pos = pos.ptr;

				_size += other.size();
				old_pos->prev->next = other._endptr->next;
				old_pos->prev = other._endptr->prev;

			}
		}


		void	sort()
		{
			if (_size > 1)
				merge_sort(&(_endptr->next));
		}
	};
};

# include "BidirectionalIterator.hpp"
#endif //FT_CONTAINERS_LIST_HPP
