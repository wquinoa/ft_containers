
#ifndef MAPBASE_HPP
# define MAPBASE_HPP

# include <memory>
# include "treeIterator.hpp"
# include "Trees/pair.hpp"
# include "Algorithm.hpp"
# include "test-related/testheader.hpp"

namespace ft
{
	template < class Key, class Value, class NodeContents, class Compare = ft::less<Key>, class Alloc = std::allocator<ft::pair<const Key,Value> > >
	class RBTree
	{
	 public:
		typedef Key																	key_type;
		typedef Value																mapped_type;
		typedef NodeContents														value_type;
		typedef	Compare																key_compare;
		typedef Alloc																allocator_type;
		typedef	value_type&															reference;
		typedef	const value_type&													const_reference;
		typedef	value_type*															pointer;
		typedef	const value_type*													const_pointer;
		typedef	size_t																size_type;
		typedef treeIterator<value_type, pointer, reference, Compare >				iterator;
		typedef treeIterator<value_type, const_pointer, const_reference, Compare >	const_iterator;
		typedef ReverseIterator<iterator>											reverse_iterator;
		typedef ReverseIterator<const_iterator>										const_reverse_iterator;

		class value_compare
		{
			friend class RBTree;
		 protected:
			Compare comp;
			explicit value_compare (Compare c) : comp(c) {}

		 public:
			bool operator() (const value_type &x, const value_type &y) const
			{ return comp(x.first, y.first); }
		};

		explicit RBTree(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type())
				: _alloc(alloc), _comp(comp), _size()
		{
		    init();
		}

		RBTree (const RBTree &x) : _alloc(x._alloc), _comp(x._comp), _size() { init(); }

		RBTree &operator= (const RBTree &x)
		{
			if (this != &x)
			{
				clear();
				_alloc = x._alloc;
				_comp = x._comp;
				insert(x.begin(), x.end());
			}
			return (*this);
		}

		virtual	~RBTree()
		{
			clear();
			delete _first;
			delete _last;
		}

# if (TEST_THEIRS == 1)
        void 	prettyprint() { postorder(_root); }
# endif

		/*
		 * Iterators
		 */

		inline iterator				    begin()         { return iterator(_first->parent); }
		inline const_iterator			begin() const   { return const_iterator(_first->parent); }
		inline iterator			    	end()           { return iterator(_last); }
		inline const_iterator			end() const     { return const_iterator(_last); }
		inline reverse_iterator		    rbegin()        { return reverse_iterator(_last->parent); }
		inline const_reverse_iterator	rbegin() const  { return const_reverse_iterator(_last->parent); }
		inline reverse_iterator		    rend()          { return reverse_iterator(_first); }
		inline const_reverse_iterator	rend() const    { return const_reverse_iterator(_first); }

		/*
		 * Size-related
		 */

		inline bool				empty() const       { return (_size == 0); }
		inline size_type		size() const        { return (_size); }
		inline size_type		max_size() const    { return SIZE_T_MAX / sizeof(RBNode<value_type, Compare>); }
		size_type		        erase(const key_type &k);
		void		        	erase(iterator position);
		void			        erase(iterator first, iterator last);
		void					clear();
		void					swap(RBTree &x);

		/*
		 * Get comparator
		 */

		key_compare				key_comp() const    { return _comp; }
		value_compare			value_comp() const  { return value_compare(_comp); }

		/*
		 * Finders
		 */

		iterator		find(const key_type &k);
		const_iterator	find(const key_type &k) const;
		size_type		count(const key_type &k) const;
		iterator		lower_bound(const key_type &k);
		const_iterator	lower_bound(const key_type &k) const;
		iterator		upper_bound(const key_type &k);
		const_iterator	upper_bound(const key_type &k) const;

		ft::pair<const_iterator,const_iterator> equal_range(const key_type &k) const
		{
		    return ft::pair<const_iterator, const_iterator>(const_iterator(lower_bound(k)), const_iterator(upper_bound(k)));
		}

		ft::pair<iterator,iterator>             equal_range(const key_type &k)
		{
		    return ft::pair<iterator, iterator>(iterator(lower_bound(k)), iterator(upper_bound(k)));
		}

	 protected:

        void postorder(RBNode<value_type, Compare>* p, int indent = 0)
        {
            if(notEndNode(p))
            {
                if(notEndNode(p->right)) {
                    postorder(p->right, indent+4);
                }
                if (indent) {
                    std::cout << std::setw(indent) << ' ';
                }
                if (notEndNode(p->right)) std::cout << " /\n" << std::setw(indent) << ' ';
                std::cout << (p->isBlack ? "\033[30;1m" : "\033[31m") << p->data.first << "\033[0;m\n ";
                if(notEndNode(p->left)) {
                    std::cout << std::setw(indent) << ' ' <<" \\\n";
                    postorder(p->left, indent+4);
                }
            }
        }

        /*
		 * Comparator overloads
		 */

		bool	cmp(const key_type &k, const ft::pair<Key, Value> &p) const                 { return key_comp()(k, p.first); }
		bool	cmp(const ft::pair<Key, Value> &p, const key_type &k) const                 { return key_comp()(p.first, k); }
		bool	cmp(const key_type &k1, const key_type &k2) const                           { return key_comp()(k1, k2); }
		bool	cmp(const ft::pair<Key, Value> &p1, const ft::pair<Key, Value> &p2) const   { return key_comp()(p1.first, p2.first); }

		/*
		 *	Special node manipulation
		 */

		RBNode<NodeContents, Compare>	        *findNode(iterator position);
		void									init();
		RBNode<NodeContents, Compare>			*relinkRoot(const value_type &val);
		void									erase_root();
		void									link_outer();
		bool									notEndNode(RBNode<NodeContents, Compare> *check);
		void									attachParent(RBNode<NodeContents, Compare> *u, RBNode<NodeContents, Compare> *v);
		RBNode<NodeContents, Compare>*			minNode(RBNode<NodeContents, Compare> *x);

		/*
		 * Rotations
		 */

		void									leftRotate(RBNode<NodeContents, Compare> *node);
		void									rightRotate(RBNode<NodeContents, Compare> *node);

		/*
		 * Insertion
		 */

		RBNode<NodeContents, Compare>			*insert_left(RBNode<NodeContents, Compare> *it, const value_type &val = value_type());
		RBNode<NodeContents, Compare>			*insert_right(RBNode<NodeContents, Compare> *it, const value_type &val = value_type());
		void									fixRedRed(RBNode<NodeContents, Compare> *z);

		/*
		 * Deletion
		 */

		void									RedBlackDelete(RBNode<NodeContents, Compare> *delNode);
		void									fixDoubleBlack(RBNode<NodeContents, Compare> *node);
		void									clear(RBNode<NodeContents, Compare> *pos);

		/*
		 * Data types
		 */

		RBNode<NodeContents, Compare>			*_root;
		RBNode<NodeContents, Compare>			*_first;
		RBNode<NodeContents, Compare>			*_last;

		allocator_type							_alloc;
		key_compare								_comp;
		size_type								_size;
	};

	///   VISIBILITY todo Size-related

	template<class Key, class Value, class NodeContents, class Compare, class Alloc>
	void
	RBTree<Key, Value, NodeContents, Compare, Alloc>::erase(RBTree::iterator position)
	{
		RBNode<NodeContents, Compare>	*erase = findNode(position);

		if (erase == end())
			return ;
		RedBlackDelete(erase);
		delete erase;
		--_size;
	}

	template<class Key, class Value, class NodeContents, class Compare, class Alloc>
	size_t
	RBTree<Key, Value, NodeContents, Compare, Alloc>::erase(const key_type &key)
	{
		iterator it = find(key);

		if (it == end())
			return 0;
		erase(it);
		return 1;
	}

	template<class Key, class Value, class NodeContents, class Compare, class Alloc>
	void
	RBTree<Key, Value, NodeContents, Compare, Alloc>::erase(RBTree::iterator first, RBTree::iterator last)
	{
		while (first != last)
		{
			erase(first);
			++first;
		}
	}

	template<class Key, class Value, class NodeContents, class Compare, class Alloc>
	void
	RBTree<Key, Value, NodeContents, Compare, Alloc>::clear()
	{
		if (not _size)
			return ;
		clear(_root);
		link_outer();
	}

	///   VISIBILITY todo Finders

	template<class Key, class Value, class NodeContents, class Compare, class Alloc>
	typename RBTree<Key, Value, NodeContents, Compare, Alloc>::iterator
	RBTree<Key, Value, NodeContents, Compare, Alloc>::find(const key_type &key)
	{
		RBNode<NodeContents, Compare>	*it(_root);

		while (it and it != _first and it != _last)
		{
			if (cmp(key, it->data))
				it = it->left;
			else if (cmp(it->data, key))
				it = it->right;
			else return iterator(it);
		}
		return end();
	}

	template<class Key, class Value, class NodeContents, class Compare, class Alloc>
	typename RBTree<Key, Value, NodeContents, Compare, Alloc>::const_iterator
	RBTree<Key, Value, NodeContents, Compare, Alloc>::find(const key_type &key) const
	{
		RBNode<NodeContents, Compare>	*it(_root);

		while (it and it != _first and it != _last)
		{
			if (cmp(key, it->data))
				it = it->left;
			else if (cmp(it->data, key))
				it = it->right;
			else return const_iterator(it);
		}
		return end();
	}

	template<class Key, class Value, class NodeContents, class Compare, class Alloc>
	size_t
	RBTree<Key, Value, NodeContents, Compare, Alloc>::count(const key_type &k) const
	{
		const_iterator	it = begin();
		const_iterator	ite = end();
		size_type		count = 0;

		while (it != ite)
		{
			if (not cmp(k, *it) and not cmp(*it, k))
				++count;
			++it;
		}
		return count;
	}

	template<class Key, class Value, class NodeContents, class Compare, class Alloc>
	typename RBTree<Key, Value, NodeContents, Compare, Alloc>::iterator
	RBTree<Key, Value, NodeContents, Compare, Alloc>::lower_bound(const key_type &key)
	{
		iterator		it = begin();
		const_iterator	ite = end();

		while (it != ite)
		{
			if (not cmp(*it, key))
				return it;
			++it;
		}
		return it;
	}

	template<class Key, class Value, class NodeContents, class Compare, class Alloc>
	typename RBTree<Key, Value, NodeContents, Compare, Alloc>::const_iterator
	RBTree<Key, Value, NodeContents, Compare, Alloc>::lower_bound(const key_type &key) const
	{
		const_iterator	it = begin();
		const_iterator	ite = end();

		while (it != ite)
		{
			if (not cmp(*it, key))
				return it;
			++it;
		}
		return it;
	}

	template<class Key, class Value, class NodeContents, class Compare, class Alloc>
	typename RBTree<Key, Value, NodeContents, Compare, Alloc>::iterator
	RBTree<Key, Value, NodeContents, Compare, Alloc>::upper_bound(const key_type &key)
	{
		iterator		it = begin();
		const_iterator	ite = end();

		while (it != ite)
		{
			if (cmp(key, *it))
				return it;
			++it;
		}
		return it;
	}

	template<class Key, class Value, class NodeContents, class Compare, class Alloc>
	typename RBTree<Key, Value, NodeContents, Compare, Alloc>::const_iterator
	RBTree<Key, Value, NodeContents, Compare, Alloc>::upper_bound(const key_type &key) const
	{
		const_iterator it = begin(), ite = end();

		while (it != ite)
		{
			if (cmp(key, *it))
				break ;
			++it;
		}
		return it;
	}

	/*** VISIBILITY todo Private member functions ***/
	/* Finders */

	template<class Key, class Value, class NodeContents, class Compare, class Alloc>
	RBNode<NodeContents, Compare> *
	RBTree<Key, Value, NodeContents, Compare, Alloc>::findNode(RBTree::iterator pos)
	{
		RBNode<NodeContents, Compare>	*it(_root);

		while (it and it != _first and it != _last)
		{
			if (cmp(*pos, it->data))
				it = it->left;
			else if (cmp(it->data, *pos))
				it = it->right;
			else return (it);
		}
		return _last;
	}

	/*** VISIBILITY todo Special node manipulation ***/

	template<class Key, class Value, class NodeContents, class Compare, class Alloc>
	void
	RBTree<Key, Value, NodeContents, Compare, Alloc>::init()
	{
		_first = new RBNode<NodeContents, Compare>();
		_last = new RBNode<NodeContents, Compare>();
		link_outer();
		_size = 0;
	}

	template<class Key, class Value, class NodeContents, class Compare, class Alloc>
	RBNode<NodeContents, Compare> *
	RBTree<Key, Value, NodeContents, Compare, Alloc>::relinkRoot(const value_type &val)
	{
		_root = new RBNode<NodeContents, Compare>(val, true);
		++_size;
		_first->parent = _last->parent = _root;
		_root->left = _first;
		_root->right = _last;
		return _root;
	}

	template<class Key, class Value, class NodeContents, class Compare, class Alloc>
	void
	RBTree<Key, Value, NodeContents, Compare, Alloc>::erase_root()
	{
		if (_size)
		{
			delete(_root);
			link_outer();
		}
	}

	template<class Key, class Value, class NodeContents, class Compare, class Alloc>
	void
	RBTree<Key, Value, NodeContents, Compare, Alloc>::link_outer()
	{
		_first->parent = _last;
		_last->parent = _first;
	}

	template<class Key, class Value, class NodeContents, class Compare, class Alloc>
	bool RBTree<Key, Value, NodeContents, Compare, Alloc>::notEndNode(RBNode<NodeContents, Compare> *check)
	{
		return (check and check != _first and check != _last);
	}

	template<class Key, class Value, class NodeContents, class Compare, class Alloc>
	void
	RBTree<Key, Value, NodeContents, Compare, Alloc>::attachParent(RBNode<NodeContents, Compare> *u,
																   RBNode<NodeContents, Compare> *v)
	{
		if (u and not u->parent) // U is root
			_root = v;
		else if (u->isLeft()) // u is left child
			u->parent->left = v;
		else // u is right child
			u->parent->right = v;
		if (v)
			v->parent = u->parent;
	}

	template<class Key, class Value, class NodeContents, class Compare, class Alloc>
	RBNode<NodeContents, Compare> *
	RBTree<Key, Value, NodeContents, Compare, Alloc>::minNode(RBNode<NodeContents, Compare> *node)
	{
		while (node->left)
			node = node->left;
		return node;
	}

	/*** VISIBILITY todo Rotations ***/

	template<class Key, class Value, class NodeContents, class Compare, class Alloc>
	void RBTree<Key, Value, NodeContents, Compare, Alloc>::leftRotate(RBNode<NodeContents, Compare> *node)
	{
		RBNode<NodeContents, Compare> *tmp = node->right;
		node->right = tmp->left;

		if (node->right) node->right->parent = node;
		tmp->parent = node->parent;

		if (not tmp->parent)
			_root = tmp;
		else if (node->isLeft())
			tmp->parent->left = tmp;
		else
			tmp->parent->right = tmp;
		tmp->left = node;
		node->parent = tmp;
	}

	template<class Key, class Value, class NodeContents, class Compare, class Alloc>
	void
	RBTree<Key, Value, NodeContents, Compare, Alloc>::rightRotate(RBNode<NodeContents, Compare> *node)
	{
		RBNode<NodeContents, Compare> *tmp = node->left;
		node->left = tmp->right;

		if (node->left) node->left->parent = node;
		tmp->parent = node->parent;

		if (not tmp->parent)
			_root = tmp;
		else if (node->isLeft())
			tmp->parent->left = tmp;
		else
			tmp->parent->right = tmp;
		tmp->right = node;
		node->parent = tmp;
	}

	/*** VISIBILITY todo Insertion ***/

	template<class Key, class Value, class NodeContents, class Compare, class Alloc>
	RBNode<NodeContents, Compare> *
	RBTree<Key, Value, NodeContents, Compare, Alloc>::insert_left(RBNode<NodeContents, Compare> *it, const value_type &val)
	{
		RBNode<NodeContents, Compare> *babyNode = new RBNode<NodeContents, Compare>(val);

		babyNode->parent = it;
		babyNode->left = it->left;
		if (it->left)
			it->left->parent = babyNode;
		it->left = babyNode;
		++_size;
		fixRedRed(babyNode);
		return babyNode;
	}

	template<class Key, class Value, class NodeContents, class Compare, class Alloc>
	RBNode<NodeContents, Compare> *
	RBTree<Key, Value, NodeContents, Compare, Alloc>::insert_right(RBNode<NodeContents, Compare> *it, const value_type &val)
	{
		RBNode<NodeContents, Compare> *babyNode = new RBNode<NodeContents, Compare>(val);

		babyNode->parent = it;
		babyNode->right = it->right;
		if (it->right)
			it->right->parent = babyNode;
		it->right = babyNode;
		++_size;
		fixRedRed(babyNode);
		return babyNode;
	}

	template<class Key, class Value, class NodeContents, class Compare, class Alloc>
	void
	RBTree<Key, Value, NodeContents, Compare, Alloc>::fixRedRed(RBNode<NodeContents, Compare> *node)
	{
		while (node != _root and not node->isBlack and not node->parent->isBlack)
		{
			RBNode<NodeContents, Compare> *parent = node->parent;
			RBNode<NodeContents, Compare> *grandparent = parent->parent;

			if (parent->isLeft())
			{
				RBNode<NodeContents, Compare> *uncle = grandparent->right;

				if (notEndNode(uncle) and not uncle->isBlack) // Case 1: uncle is red
				{
					grandparent->isBlack = false;
					parent->isBlack = true;
					uncle->isBlack = true;
					node = grandparent;
				}
				else if (not node->isLeft()) // Case 2: Node is right child
				{
					leftRotate(parent);
					node = parent;
					parent = node->parent;
				}
				else  // Case 3: Node is left child of parent
				{
					rightRotate(grandparent);
					ft::swap(parent->isBlack, grandparent->isBlack);
				}
			}
			else
			{
				RBNode<NodeContents, Compare> *uncle = grandparent->left;

				if (notEndNode(uncle) and not uncle->isBlack)  // Case 1: uncle is red
				{
					grandparent->isBlack = false;
					parent->isBlack = true;
					uncle->isBlack = true;
					node = grandparent;
				}
				else if (node->isLeft()) // Case 2: Node is left child
				{
					rightRotate(parent);
					node = parent;
					parent = node->parent;
				}
				else
				{
					leftRotate(grandparent);
					ft::swap(parent->isBlack, grandparent->isBlack);
					node = parent;
				}
			}
		}
		_root->isBlack = true;
	}

	/*** VISIBILITY todo Deletion ***/

	template<class Key, class Value, class NodeContents, class Compare, class Alloc>
	void
	RBTree<Key, Value, NodeContents, Compare, Alloc>::RedBlackDelete(RBNode<NodeContents, Compare> *delNode)
	{
		RBNode<NodeContents, Compare> *clone = delNode;
		RBNode<NodeContents, Compare> *lowNode;

		bool  WasBlack = clone->isBlack;
		if (not delNode->left)  // no children, or only right child
		{
			lowNode = delNode->right;
			attachParent(delNode, delNode->right);
		}
		else if (not delNode->right)  // only left child
		{
			lowNode = delNode->left;
			attachParent(delNode, delNode->left);
		}
		else  // two children
		{
			clone = minNode(delNode->right);
			WasBlack = clone->isBlack;
			lowNode = clone->right;
			if (clone->parent == delNode)
			{
				if (lowNode) lowNode->parent = clone;
			}
			else
			{
				attachParent(clone, clone->right);
				clone->right = delNode->right;
				clone->right->parent = clone;
			}
			attachParent(delNode, clone);
			clone->left = delNode->left;
			clone->left->parent = clone;
			clone->isBlack = delNode->isBlack;
		}
		if (WasBlack)
			fixDoubleBlack(lowNode);
	}

	template<class Key, class Value, class NodeContents, class Compare, class Alloc>
	void
	RBTree<Key, Value, NodeContents, Compare, Alloc>::fixDoubleBlack(RBNode<NodeContents, Compare> *node)
	{
		if (not node) return ;

		while (node != _root and node->isBlack)
		{
			if (node->isLeft())  // Case A
			{
				RBNode<NodeContents, Compare> *sibling = node->parent->right;
				if (not sibling->isBlack)  // Case 1
				{
					sibling->isBlack = true;
					node->parent->isBlack = false;
					leftRotate(node->parent);
					sibling = node->parent->right;
				}
				if (sibling->left and sibling->left->isBlack and sibling->right and sibling->right->isBlack)  // case 2
				{
					sibling->isBlack = false;
					node = node->parent;
				}
				else // Case 3 or 4
				{
					if (sibling->right and sibling->right->isBlack) // Case 3
					{
						sibling->left->isBlack = true;
						sibling->isBlack = false;
						rightRotate(sibling);
						sibling = node->parent->right;
					}
					else // Case 4
					{
						sibling->isBlack = node->parent->isBlack;
						node->parent->isBlack = true;
						sibling->right ? sibling->right->isBlack = true : 0;
						leftRotate(node->parent);
						node = _root;
					}
				}
			}
			else // Case B
			{
				RBNode<NodeContents, Compare> *sibling = node->parent->left;
				if (not sibling->isBlack) // Case 1
				{
					sibling->isBlack = true;
					node->parent->isBlack = false;
					rightRotate(node->parent);
					sibling = node->parent->left;
				}
                if (sibling->left and sibling->left->isBlack and sibling->right and sibling->right->isBlack)  // case 2
				{
					sibling->isBlack = false;
					node = node->parent;
				}
				else // Case 3 or 4
				{
					if (sibling->left and sibling->left->isBlack) // Case 3
					{
						sibling->right->isBlack = true;
						sibling->isBlack = false;
						leftRotate(sibling);
						sibling = node->parent->left;
					}
					else // Case 4
					{
						sibling->isBlack = node->parent->isBlack;
						node->parent->isBlack = true;
                        sibling->left ? sibling->left->isBlack = true : 0;
						rightRotate(node->parent);
						node = _root;
					}
				}
			}
		}
		node->isBlack = true;
	}

	template<class Key, class Value, class NodeContents, class Compare, class Alloc>
	void
	RBTree<Key, Value, NodeContents, Compare, Alloc>::clear(RBNode<NodeContents, Compare> *pos)
	{
		if (!pos) return ;

		clear(pos->left);
		clear(pos->right);
		if (pos != _first and pos != _last)
		{
			delete pos;
			--_size;
		}
	}

	template<class Key, class Value, class NodeContents, class Compare, class Alloc>
	void
	RBTree<Key, Value, NodeContents, Compare, Alloc>::swap(RBTree &other)
	{
		ft::swap(_last, other._last);
		ft::swap(_first, other._first);
		ft::swap(_root, other._root);
		ft::swap(_alloc, other._alloc);
		ft::swap(_comp, other._comp);
		ft::swap(_size, other._size);
	}

	/*** VISIBILITY todo Comparison operators ***/

    template <class Key, class Value, class Compare, class Alloc>
    bool operator== (const RBTree<Key,Value,ft::pair<Key, Value>, Compare, Alloc> &lhs, const RBTree<Key,Value,ft::pair<Key, Value>, Compare, Alloc> &rhs)
    {
        return not (lexicographical_equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
    }

	template <class Key, class Value, class Compare, class Alloc>
	bool operator!= (const RBTree<Key,Value,ft::pair<Key, Value>, Compare, Alloc> &lhs, const RBTree<Key,Value,ft::pair<Key, Value>, Compare, Alloc> &rhs)
	{
		return not (lhs == rhs);
	}

	template <class Key, class Value, class Compare, class Alloc>
	bool operator<  (const RBTree<Key,Value,ft::pair<Key, Value>, Compare, Alloc> &lhs, const RBTree<Key,Value,ft::pair<Key, Value>, Compare, Alloc> &rhs)
	{
		return ft::lexicographical_less(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template <class Key, class Value, class Compare, class Alloc>
	bool operator>  (const RBTree<Key,Value,ft::pair<Key, Value>, Compare, Alloc> &lhs, const RBTree<Key,Value,ft::pair<Key, Value>, Compare, Alloc> &rhs)
	{
		return (rhs < lhs);
	}

	template <class Key, class Value, class Compare, class Alloc>
	bool operator<= (const RBTree<Key,Value,ft::pair<Key, Value>, Compare, Alloc> &lhs, const RBTree<Key,Value,ft::pair<Key, Value>, Compare, Alloc> &rhs)
	{
		return not (lhs > rhs);
	}

	template <class Key, class Value, class Compare, class Alloc>
	bool operator>= (const RBTree<Key,Value,ft::pair<Key, Value>, Compare, Alloc> &lhs, const RBTree<Key,Value,ft::pair<Key, Value>, Compare, Alloc> &rhs)
	{
		return not (lhs < rhs);
	}

} // ft namespace



#endif