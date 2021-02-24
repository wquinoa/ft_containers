//
// Created by user on 21.02.2021.
//

#ifndef FT_CONTAINERS_MAP_HPP
#define FT_CONTAINERS_MAP_HPP
#include "RBTree.hpp"

namespace ft
{
	template<class Key, class Value, class Compare = less <Key>, class Alloc = std::allocator <ft::pair<const Key, Value> > >
	class Map : public RBTree<const Key, Value, ft::pair<const Key, Value>, Compare, Alloc>
	{
	 public:
		typedef RBTree<const Key, Value, ft::pair<const Key, Value>, Compare, Alloc> Base;
		using typename Base::key_type;
		using typename Base::mapped_type;
		using typename Base::value_type;
		using typename Base::key_compare;
		using typename Base::allocator_type;
		using typename Base::reference;
		using typename Base::const_reference;
		using typename Base::pointer;
		using typename Base::const_pointer;
		using typename Base::iterator;
		using typename Base::const_iterator;
		using typename Base::reverse_iterator;
		using typename Base::const_reverse_iterator;
		using typename Base::size_type;

		// Constructors, destructors and operator=
		explicit Map(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type())
				: Base(comp, alloc)
		{
		}

		template<class InputIt>
		Map(InputIt first, InputIt last, const key_compare &comp = key_compare(),
			const allocator_type &alloc = allocator_type(),
			typename has_iterator_category<InputIt>::value = false) : Base(comp, alloc)
		{
			this->insert(first, last);
		}

		Map(const Map &x) : Base()
		{
			this->insert(x.begin(), x.end());
		}

		virtual    ~Map()
		{
		}

		Map &operator=(const Map &copy)
		{
			if (this != &copy)
			{
				this->clear();
				this->_alloc = copy._alloc;
				this->_comp = copy._comp;
	    		this->insert(copy.begin(), copy.end());
			}
			return (*this);
		}

		mapped_type &operator[](const key_type &k)
		{
			return insert(ft::pair<key_type, mapped_type>(k, mapped_type())).first->second;
		}

		ft::pair<iterator, bool> insert(const value_type &val)
		{
			RBNode <value_type, Compare> *it = Base::_root;

			if (Base::_size == 0)
				return (ft::pair<iterator, bool>(iterator(Base::relinkRoot(val)), true));

			while (it)
			{
				if (key_compare()(val.first, it->data.first))
				{
					if (it->left and it->left != this->_first)
						it = it->left;
					else return ft::pair<iterator, bool>(iterator(Base::insert_left(it, val)), true);
				}
				else if (key_compare()(it->data.first, val.first))
				{
					if (it->right and it->right != this->_last)
						it = it->right;
					else return ft::pair<iterator, bool>(iterator(Base::insert_right(it, val)), true);
				}
				else break;
			}
			return ft::pair<iterator, bool>(iterator(it), false);
		}

		iterator insert(iterator position, const value_type &val)
		{
			(void) position;
			return insert(val).first;
		}

		template<class InputIt>
		void insert(InputIt first, InputIt last)//, typename ft::has_iterator_category<InputIt>::value = false)
		{
			while (first != last)
			{
				insert(*first);
				++first;
			}
		}
    };

    template <class Key, class Value, class Compare, class Alloc>
    bool operator== (const Map<Key, Value, Compare, Alloc> &lhs, const Map<Key, Value, Compare, Alloc> &rhs)
    {
        return  ft::lexicographical_equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }

    template <class Key, class Value, class Compare, class Alloc>
    bool operator!= (const Map<Key, Value, Compare, Alloc> &lhs, const Map<Key, Value, Compare, Alloc> &rhs)
    {
        return not (lhs == rhs);
    }

    template <class Key, class Value, class Compare, class Alloc>
    bool operator<  (const Map<Key, Value, Compare, Alloc> &lhs, const Map<Key, Value, Compare, Alloc> &rhs)
    {
        return ft::lexicographical_less(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }

    template <class Key, class Value, class Compare, class Alloc>
    bool operator>  (const Map<Key, Value, Compare, Alloc> &lhs, const Map<Key, Value, Compare, Alloc> &rhs)
    {
        return (rhs < lhs);
    }

    template <class Key, class Value, class Compare, class Alloc>
    bool operator<= (const Map<Key, Value, Compare, Alloc> &lhs, const Map<Key, Value, Compare, Alloc> &rhs)
    {
        return not (lhs > rhs);
    }

    template <class Key, class Value, class Compare, class Alloc>
    bool operator>= (const Map<Key, Value, Compare, Alloc> &lhs, const Map<Key, Value, Compare, Alloc> &rhs)
    {
        return not (lhs < rhs);
    }
}

#endif //FT_CONTAINERS_MAP_HPP
