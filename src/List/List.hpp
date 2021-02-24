//
// Created by user on 05.02.2021.
//

#ifndef FT_CONTAINERS_LIST_HPP
# define FT_CONTAINERS_LIST_HPP
# include "Iterator.hpp"
# include "DNode.hpp"
# include "Algorithm.hpp"
# include <memory>

namespace ft
{
	template<typename T, typename Pointer, typename Reference>
	class BidirectionalIterator;

	template <class T, class Allocator = std::allocator<T> >
	class List
	{
	 public:
		typedef T													value_type;
		typedef DNode<T>											node;
		typedef Allocator											allocator_type;
		typedef size_t												size_type;
		typedef ptrdiff_t											difference_type;
		typedef typename Allocator::reference						reference;
		typedef typename Allocator::const_reference					const_reference;
		typedef typename Allocator::pointer							pointer;
		typedef typename Allocator::const_pointer					const_pointer;
		typedef ft::BidirectionalIterator<T, T*, T& >				iterator;
		typedef ft::BidirectionalIterator<T, const T *, const T &> 	const_iterator;
		typedef ft::ReverseIterator<iterator> 						reverse_iterator;
		typedef ft::ReverseIterator<const_iterator> 				const_reverse_iterator;

	 private:
		node                *_endptr;
		size_type           _size;
		allocator_type      _alloc;

		void				createEndNode();
		node				*erase_ptr(node *ptr);
		template <class C>
		node				*merge(node *a, node *b, C comp);
		template <class C>
		void				merge_sort(node **head, size_type size, C comparator);

	 public:

		List();
		explicit List(const allocator_type &alloc);
		explicit List(size_type n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type());
		explicit List(size_type n);

		template<class InputIt>
		List(InputIt first, InputIt last, const allocator_type &alloc = allocator_type(),
				typename ft::has_iterator_category<InputIt>::value = false);

		List( const List& other );
		List &operator= (const List &other);

		~List();

		/***
		 ***  VISIBILITY todo Element access
		 ***/

		iterator 			end()			{ return iterator(_endptr); }
		const_iterator 		end() const		{ return iterator(_endptr); }
		reverse_iterator 	rend()			{ return reverse_iterator(_endptr); }
		iterator 			begin()			{ return iterator(_endptr->next); }
		const_iterator 		begin() const	{ return iterator(_endptr->next); }
		reverse_iterator 	rbegin()		{ return reverse_iterator(_endptr->prev); }
		reference 			front()			{ return _endptr->next->data; }
		const_reference		front() const	{ return _endptr->next->data; }
		reference			back()			{ return _endptr->prev->data; }
		const_reference		back() const	{ return _endptr->prev->data; }

		/*
		 * size
		 */

		bool				empty() const	{ return not _size; }
		size_type			size() const	{ return _size; }
		size_type			max_size() const { return SIZE_T_MAX / sizeof(node); }

		/*
		 * push pop
		 */

		void				push_front(const value_type & value);
		void				push_back(const value_type &value);
		void				pop_front();
		void				pop_back();

		/*
		 * erase assign etc
		 */

		iterator 			insert(iterator position, const value_type &val);
		void 				insert(iterator position, size_type n, const value_type &val);
		template< class InputIt >
		void 				insert(iterator position, InputIt first, InputIt last, typename ft::has_iterator_category<InputIt>::value = false);

		iterator 			erase(iterator first, iterator last);
		iterator 			erase(iterator position);
		void				clear();

		template <class InputIt>
		void 				assign(InputIt first, InputIt last, typename ft::has_iterator_category<InputIt>::value = false);
		void				assign(size_type n, const value_type& value);

		void				resize(size_type n, value_type val = value_type());

		/*
		 *	Operations
		 */

		template<class UnaryPredicate>
		void				remove_if(UnaryPredicate predicate);
		void				remove(const_reference value);
		template <class BinaryPredicate>
		void 				unique(BinaryPredicate predicate);
		void				reverse();
		template <class Compare>
		void				merge(List &other, Compare comp);
		void				merge(List &other);
		void				splice(const_iterator position, List &other);
		void				splice(const_iterator position, List &other, const_iterator element);
		void				splice(const_iterator position, List &other, const_iterator first, const_iterator last);
		template< class Compare >
		void				sort(Compare comparator);
		void				sort();
		void				swap(List &copy);

		/*
		 *  Relational operators
		 */

		friend bool operator==(const List &lhs, const List &rhs)
		{
			return ft::lexicographical_equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
		}

		friend bool operator< (const List &lhs, const List &rhs)
		{
			return ft::lexicographical_less(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
		}

		friend bool operator> (const List &lhs, const List &rhs) { return rhs < lhs; }
		friend bool operator<=(const List &lhs, const List &rhs) { return not (rhs < lhs); }
		friend bool operator>=(const List &lhs, const List &rhs) { return not (lhs < rhs); }
		friend bool operator!=(const List &lhs, const List &rhs) { return not (rhs == lhs); }
	};

	///  VISIBILITY todo Private utility members

	template <typename T, class Allocator>
	void		List<T, Allocator>::createEndNode()
	{
		_endptr = new node();
		_endptr->next = _endptr;
		_endptr->prev = _endptr;
	}

	template<class T, class Allocator>
	DNode<T> 	*List<T, Allocator>::erase_ptr(List::node *ptr)
	{
		node *rv = ptr->next;

		ptr->next->prev = ptr->prev;
		ptr->prev->next = ptr->next;
		--_size;
		delete ptr;
		return rv;
	}

	///   VISIBILITY todo Merge sort

	template<class T, class Allocator>
	template<class Compare>
	DNode<T> 	*List<T, Allocator>::merge(List::node *a, List::node *b, Compare comp)
	{
		/* No more nodes - ascend */
		if (a == _endptr)
			return (b);
		if (b == _endptr)
			return (a);

		node *result;

		/* Pick either a or b, and recur */
		if (comp(a->data, b->data))
		{
			result = a;
			result->next = merge(a->next, b, comp);
			a->next = result->next;
			result->next->prev = a;
		}
		else
		{
			result = b;
			result->next = merge(a, b->next, comp);
			b->next = result->next;
			result->next->prev = b;
		}
		return (result);
	}

	template<class T, class Allocator>
	template<class Compare>
	void List<T, Allocator>::merge_sort(List::node **lst, List::size_type size, Compare comp)
	{
		/* Promise the older calls to split lists */
		if (size < 2)
			return;

		node *b;

		size_t half_size = size / 2;
		node* slow = *lst;

		/* Split everything */
		size -= half_size;
		while (half_size-- > 1)
			slow = slow->next;
		b = slow->next;
		slow->next = _endptr;

		merge_sort(lst, size, comp);
		merge_sort(&b, size, comp);

		/* Assemble everything */
		*lst = merge(*lst, b, comp);
	}

	///   VISIBILITY todo Copliens

	template<class T, class Allocator>
	List<T, Allocator>::List() : _endptr(), _size(), _alloc()
	{
		createEndNode();
	}

	template<class T, class Allocator>
	List<T, Allocator>::List(const allocator_type &alloc) : _size(), _alloc(alloc)
	{
		createEndNode();
	}

	template<class T, class Allocator>
	List<T, Allocator>::List(List::size_type n) : _size(n), _alloc()
	{
		createEndNode();
	}

	template<class T, class Allocator>
	template<class InputIt>
	List<T, Allocator>::List(InputIt first, InputIt last, const allocator_type &alloc,
			typename ft::has_iterator_category<InputIt>::value yes) : _alloc(alloc)
	{
		if (yes)
		{
			createEndNode();
			assign(first, last);
		}
	}

	template<class T, class Allocator>
	List<T, Allocator>::List(List::size_type n, const value_type &val, const allocator_type &alloc)
	: _size(), _alloc(alloc)
	{
		createEndNode();
		assign(n, val);
	}

	template<class T, class Allocator>
	List<T, Allocator> &List<T, Allocator>::operator=(const List &other)
	{
		if (this != &other)
		{
			createEndNode();
			clear();
			_alloc = other._alloc;
			_endptr->next = _endptr;
			_endptr->prev = _endptr;
			const_iterator it = other.begin();

			for (; it != other.end(); ++it)
				push_back(*it);
		}
		return (*this);
	}

	template<class T, class Allocator>
	List<T, Allocator>::List(const List &other)
	{
		*this = other;
	}


	template<class T, class Allocator>
	List<T, Allocator>::~List()
	{
		clear();
		delete _endptr;
	}

	/// VISIBILITY todo push-pop

	template<class T, class Allocator>
	void List<T, Allocator>::push_front(const value_type &val)
	{
		node *tmp = _endptr->next;

		_endptr->next = new node(val);
		_endptr->next->prev = _endptr;
		tmp->prev = _endptr->next;
		_endptr->next->next = tmp;
		++_size;
	}

	template<class T, class Allocator>
	void List<T, Allocator>::push_back(const value_type &val)
	{
		node *to_add = new node(val);

		to_add->next = _endptr;
		to_add->prev = _endptr->prev;
		_endptr->prev = to_add;
		to_add->prev->next = to_add;
		++_size;
	}

	template<class T, class Allocator>
	void List<T, Allocator>::pop_front()
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

	template<class T, class Allocator>
	void List<T, Allocator>::pop_back()
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

	template<class T, class Allocator>
	void List<T, Allocator>::clear()
	{
		if (_size)
			erase(begin(), end());
	}

	/// VISIBILITY todo Insertion and removal

	template<class T, class Allocator>
	template<class InputIt>
	void List<T, Allocator>::insert(List::iterator pos, InputIt first, InputIt last,
									typename ft::has_iterator_category<InputIt>::value yes)

	{
		while (first != last)
		{
			insert(pos, *first);
			++first;
		}
		(void)yes;
	}


	template<class T, class Allocator>
	void List<T, Allocator>::insert(List::iterator pos, List::size_type n, const value_type &val)
	{
		for ( ; n > 0; --n)
			insert(pos, val);
	}

	template<class T, class Allocator>
	typename List<T, Allocator>::iterator
	List<T, Allocator>::insert(List::iterator pos, const value_type &val)
	{
		node *elem = new node(val);

		elem->prev = pos.ptr;
		elem->next = pos.ptr->next;
		elem->next->prev = elem;
		elem->prev->next = elem;
		++_size;
		return (++pos);
	}

	template<class T, class Allocator>
	typename List<T, Allocator>::iterator
	List<T, Allocator>::erase(List::iterator first, List::iterator last)
	{
		while (first != last)
			first = erase(first);
		return first;
	}

	template<class T, class Allocator>
	typename List<T, Allocator>::iterator
	List<T, Allocator>::erase(List::iterator pos)
	{
		return erase_ptr(pos.ptr);
	}

	template<class T, class Allocator>
	template<class InputIt>
	void List<T, Allocator>::assign(InputIt first, InputIt last, typename ft::has_iterator_category<InputIt>::value yes)
	{
		iterator b;
		iterator e;

		/* reassign old nodes */
		for (b = begin(), e = end(); first != last and b != e; ++b, ++first)
			*b = *first;
		/* delete excess nodes */
		erase(b, e);
		/* add new nodes */
		insert(first, last);
		(void)yes;
	}

	template<class T, class Allocator>
	void List<T, Allocator>::assign(List::size_type n, const value_type &val)
	{
		iterator b = begin();
		iterator e = end();

		/* reassign old nodes */
		for (; b != e and n > 0; ++b, --n)
			*b = val;
		/* delete excess nodes */
		erase(b, e);
		/* add new nodes */
		for (; n > 0; --n)
			push_back(val);
	}

	template<class T, class Allocator>
	void List<T, Allocator>::resize(List::size_type n, value_type val)
	{
		while (_size > n)
			pop_back();
		while (_size < n)
			push_back(val);
	}

	///  VISIBILITY todo Operations

	template<class T, class Allocator>
	void List<T, Allocator>::remove(const_reference value)
	{
		iterator it, _end;

		it = begin();
		_end = end();
		while (it != _end)
		{
			if (*it == value)
				it = erase(it);
			else
				++it;
		}
	}

	template<class T, class Allocator>
	template<class UnaryPredicate>
	void List<T, Allocator>::remove_if(UnaryPredicate p)
	{
		iterator it = begin();
		iterator _end = end();

		while (it != _end)
		{
			if (p(*it))
				it = erase(it);
			else
				++it;
		}
	}

	template<class T, class Allocator>
	template<class BinaryPredicate>
	void List<T, Allocator>::unique(BinaryPredicate p)
	{
		node *it = begin().ptr;

		while (it ->next != _endptr)
		{
			if (p(it->data, it->next->data))
				it = erase_ptr(it);
			else
				++it;
		}
	}

	template<class T, class Allocator>
	void List<T, Allocator>::reverse()
	{
		node *it = _endptr->next;
		node *r_it = _endptr->prev;
		value_type tmp;

		while (it->prev != r_it)
		{
			tmp = it->data;
			it->data = r_it->data;
			r_it->data = tmp;

			it = it->next;
			r_it = r_it->prev;
		}
	}

	template<class T, class Allocator>
	template<class Compare>
	void List<T, Allocator>::merge(List &other, Compare comp)
	{
		splice(begin(), other);
		sort(comp);
	}

	template<class T, class Allocator>
	void List<T, Allocator>::merge(List &other)
	{
		merge(other, ft::less<T>());
	}

	// the real splice
	template<class T, class Allocator>
	void List<T, Allocator>::splice(List::const_iterator pos, List &other, List::const_iterator first,
									List::const_iterator last)
	{
		difference_type other_size = ft::distance(first, last);
		other._size -= other_size;
		this->_size += other_size;

		/* Isolate and relink other list */

		node *other_first = first.ptr;
		node *other_last = last.ptr->prev;

		other_first->prev->next = last.ptr;
		last.ptr->prev = other_first->prev;

		/* Insert the new slice into self */

		pos.ptr->prev->next = other_first;
		other_first->prev = pos.ptr->prev;
		pos.ptr->prev = other_last;
		other_last->next = pos.ptr;
	}

	template<class T, class Allocator>
	void List<T, Allocator>::splice(List::const_iterator pos, List &other, List::const_iterator it)
	{
		splice(pos, other, it, other.end());
	}

	template<class T, class Allocator>
	void List<T, Allocator>::splice(List::const_iterator pos, List &other)
	{
		splice(pos, other, other.begin(), other.end());
	}

	template<class T, class Allocator>
	template<class Compare>
	void List<T, Allocator>::sort(Compare comp)
	{
		merge_sort(&(_endptr->next), _size, comp);

		/* relink prev */

		node *tmp = _endptr->next;
		tmp->prev = _endptr;
		while (tmp->next != _endptr)
		{
			tmp->next->prev = tmp;
			tmp = tmp->next;
		}
		tmp->next->prev = tmp;
	}

	template<class T, class Allocator>
	void List<T, Allocator>::sort()
	{
		sort(ft::less<value_type>());
	}

	template<class T, class Allocator>
	void List<T, Allocator>::swap(List &other)
	{
		ft::swap(_endptr, other._endptr);
		ft::swap(_size, other._size);
		ft::swap(_alloc, other._alloc);
	}

	template< class T, class Alloc >
	void swap( ft::List<T,Alloc>& lhs, ft::List<T,Alloc>& rhs ) { lhs.swap(rhs); }
};

# include "BidirectionalIterator.hpp"
#endif //FT_CONTAINERS_LIST_HPP
