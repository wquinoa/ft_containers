//
// Created by user on 31.01.2021.
//

// DAta structures https://www.youtube.com/watch?v=RBSGKlAvoiM

#ifndef FT_CONTAINERS_BTREE_HPP
# define FT_CONTAINERS_BTREE_HPP
# include <memory>
# include <iostream>
# include "Algorithm.hpp"
# include <string>
# include <iomanip>
# include <map>

namespace ft
{
    template<class T, class M>
    struct pair
    {
        T first;
        M second;

        pair() : first(), second()
        {
        }

        pair(T const &f, M const &s) : first(f), second(s)
        {
        }

        pair(const pair &copy) : first(copy.first), second(copy.second)
        {
        }

        pair &operator=(const pair &copy)
        {
            if (this != &copy)
            {
                first(copy.first);
                second(copy.second);
            }
            return (*this);
        }

        bool operator==(const pair &rhs) const { return first == rhs.first and second == rhs.second; }

        bool operator!=(const pair &rhs) const { return !(rhs == *this); }
    };

	template <class T>
	struct RBNode
	{
		T			data;
		RBNode<T>	*left;
		RBNode<T>	*right;
		RBNode<T>	*parent;
		bool		isRed;

		RBNode() : data(), left(), right(), parent(), isRed(true) {};
		RBNode(T data) : data(data), left(), right(), parent(), isRed(true) {};

		bool	isLeft() { return this == parent->left; }
		RBNode	*grandparent() { return parent->parent; };
		RBNode	*getUncle() { return parent->isLeft() ? parent->parent->right : parent->parent->left; }
		RBNode	*_sibling() { return this->isLeft() ? parent->right : parent->left; }
	};

	template <class T, class M = T, class Compare = ft::less<T>, bool isUnique = true>
	class RBTree
	{
	 public:
		typedef RBNode<T>   node_type;
		typedef M           value_type;


		RBTree() :_endptr(new RBNode<T>), root(_endptr), comp(Compare())
		{
			_endptr->left = 0;
			_endptr->parent = 0;
			_endptr->right = 0;
			_endptr->isRed = false;
		}

		void        insert(T key);
		RBNode<T>   *search(T key);
		void        erase(T key);
		void        prettyprint();

	 private:
		void        postorder(node_type* parent, int indent = 0);
		void        leftRotate(RBNode<T> *);
		void        rightRotate(RBNode<T> *);

		void        eraseNode(RBNode<T> *);
		void        deletionRebalance(RBNode<T> *);
		RBNode<T>   *leftNodeRebalance(RBNode<T> *);
		RBNode<T>   *rightNodeRebalance(RBNode<T> *);

		void        fixRedRed(RBNode<T> *);
		RBNode<T>   *findSuccessor(RBNode<T> *);

		RBNode<T>	*_endptr;
		RBNode<T>	*root;
		Compare		comp;
		size_t 		size;

	};


	template <class T, class M, class Compare, bool isUnique>
	void RBTree<T, M, Compare, isUnique>::postorder(node_type* parent, int indent)
	{
		if (parent != _endptr)
		{
			if (parent->right != _endptr) postorder(parent->right, indent+4);
			if (indent) std::cout << std::setw(indent) << ' ';
			if (parent->right != _endptr) std::cout << " /\n" << std::setw(indent) << ' ';
			std::cout << (parent->isRed ? "\033[31;1m" : "\033[30m") << parent->data << "\033[0;m\n ";
			if (parent->left != _endptr) {
				std::cout << std::setw(indent) << ' ' <<" \\\n";
				postorder(parent->left, indent+4);
			}
		}
	}

	template <class T, class M, class Compare, bool isUnique>
	void RBTree<T, M, Compare, isUnique>::prettyprint()
	{
		postorder(root);
	}

	template <class T, class M, class Compare, bool isUnique>
	void RBTree<T, M, Compare, isUnique>::insert(T key)
	{
		RBNode<T>* baby;
		RBNode<T>* tmp = root;
		RBNode<T>* nparent = _endptr;

		while (tmp != _endptr)
		{
			nparent = tmp;
			if (comp(key, tmp->data))
				tmp = tmp->left;
			else if (comp(tmp->data, key))
				tmp = tmp->right;
			else return ; // key already exists
		}
		baby = new RBNode<T>(key);
		baby->parent = nparent;
		baby->left = _endptr;
		baby->right = _endptr;
		if (nparent == _endptr) {
			root = baby;
			_endptr->parent = baby;
		}
		else
		{
			if (comp(baby->data, nparent->data))
				nparent->left = baby;
			else
				nparent->right = baby;
		}
		fixRedRed(baby);
		if (size and comp(_endptr->parent->data, baby->data))
			_endptr->parent = baby;
		++size;
	}

	template <class T, class M, class Compare, bool isUnique>
	RBNode<T> *RBTree<T, M, Compare, isUnique>::search(T key)
	{
		RBNode<T> *node = root;

		while (node != _endptr)
		{
			if (comp(key, node->data))
				node = node->left;
			else if (comp(node->data, key))
				node = node->right;
			else break;
		}
		return node;
	}

	template <class T, class M, class Compare, bool isUnique>
	void RBTree<T, M, Compare, isUnique>::erase(T key)
	{
		RBNode<T> *node = search(key);
		if (node != _endptr)
		{
			if (node == _endptr->parent) // relink end()
				_endptr->parent = _endptr->grandparent();
			eraseNode(node);
		}
	}

	template <class T, class M, class Compare, bool isUnique>
	RBNode<T> *RBTree<T, M, Compare, isUnique>::findSuccessor(RBNode<T> *node)
	{
		RBNode<T> *ret = node->parent;

		if (node->right != _endptr)
		{
			while (node->left != _endptr)
				node = node->left;
			return node;
		}
		while (ret != _endptr and not node->isLeft())
		{
			node = ret;
			ret = ret->parent;
		}
		return ret;
	}

	template <class T, class M, class Compare, bool isUnique>
	void RBTree<T, M, Compare, isUnique>::leftRotate(RBNode<T> *node)
	{
		RBNode<T> *tmp = node->right;

		if (node->parent == _endptr)
			root = tmp;
		else
		{
			if (node->isLeft())
				node->parent->left = tmp;
			else
				node->parent->right = tmp;
		}
		tmp->parent = node->parent;
		node->right = tmp->left;
		tmp->left->parent = node;
		tmp->left = node;
		node->parent = tmp;
	}

	template <class T, class M, class Compare, bool isUnique>
	void RBTree<T, M, Compare, isUnique>::rightRotate(RBNode<T> *node)
	{
		RBNode<T> *tmp = node->left;

		if (node->parent == _endptr)
			root = tmp;
		else
		{
			if (node->isLeft())
				node->parent->left = tmp;
			else
				node->parent->right = tmp;
		}
		tmp->parent = node->parent;
		node->left = tmp->right;
		tmp->right->parent = node;
		tmp->right = node;
		node->parent = tmp;
	}

	template <class T, class M, class Compare, bool isUnique>
	void RBTree<T, M, Compare, isUnique>::fixRedRed(RBNode<T> *node)
	{
		RBNode<T> *uncle, *grandparent;

		while (node->parent->isRed)
		{
			uncle = node->getUncle();
			grandparent = node->grandparent();
			if (node->parent->isLeft())
			{
				if (uncle->isRed)
				{
					node->parent->isRed = false;
					uncle->isRed = false;
					grandparent->isRed = true;
					node = grandparent;
				}
				else
				{
					if (not node->isLeft())
					{
						node = node->parent;
						grandparent = node->grandparent();
						leftRotate(node);
					}
					node->parent->isRed = false;
					grandparent->isRed = true;
					node->_sibling()->isRed = false;
					rightRotate(grandparent);
				}
			}
			else
			{
				if (uncle->isRed)
				{
					node->parent->isRed = false;
					uncle->isRed = false;
					grandparent->isRed = true;
					node = grandparent;
				}
				else
				{
					if (node->isLeft())
					{
						node = node->parent;
						grandparent = node->grandparent();
						rightRotate(node);
					}
					node->parent->isRed = false;
					grandparent->isRed = true;
					node->_sibling()->isRed = false;
					leftRotate(grandparent);
				}
			}
		}
		root->isRed = false;
	}

	template <class T, class M, class Compare, bool isUnique>
	void RBTree<T, M, Compare, isUnique>::eraseNode(RBNode<T> *node)
	{
		RBNode<T> *successor;
		RBNode<T> *toDelete;
		bool twoChildren;

		twoChildren = (node->left != _endptr and node->right != _endptr);
		toDelete = (twoChildren) ? findSuccessor(node) : node;
		successor = (toDelete->left != _endptr) ? toDelete->left : toDelete->right;
		successor->parent = toDelete->parent;
		if (toDelete->parent == _endptr)
			root = successor;
		else
		{
			if (toDelete->isLeft())
				toDelete->parent->left = successor;
			else
				toDelete->parent->right = successor;
		}
		node->data = toDelete->data;
		deletionRebalance(successor);
		delete toDelete;
		--size;
	}

	template <class T, class M, class Compare, bool isUnique>
	void RBTree<T, M, Compare, isUnique>::deletionRebalance(RBNode<T> * node)
	{
		if (node->isRed)
			return ;
		while (node != root and not node->isRed)
		{
			if (node->isLeft())
				node = leftNodeRebalance(node);
			else
				node = rightNodeRebalance(node);
		}
		node->isRed = false;
	}

	template <class T, class M, class Compare, bool isUnique>
	RBNode<T> *RBTree<T, M, Compare, isUnique>::leftNodeRebalance(RBNode<T> *node)
	{
		RBNode<T> *sibling = node->_sibling();

		if (sibling->isRed)
		{
			sibling->isRed = false;
			sibling->parent->isRed = true;
			leftRotate(sibling->parent);
			sibling = node->parent->right;
		}
		if (not sibling->left->isRed and not sibling->right->isRed)
		{
			sibling->isRed = true;
			return node->parent;
		}
		else
		{
			if (not sibling->right->isRed)
			{
				sibling->left->isRed = false;
				sibling->isRed = true;
				rightRotate(sibling);
				sibling = node->parent->right;
			}
			sibling->isRed = node->parent->isRed;
			node->parent->isRed = false;
			sibling->right->isRed = false;
			leftRotate(node->parent);
			return root;
		}
	}

	template <class T, class M, class Compare, bool isUnique>
	RBNode<T> *RBTree<T, M, Compare, isUnique>::rightNodeRebalance(RBNode<T> *node)
	{
		RBNode<T> *sibling = node->_sibling();

		if (sibling->isRed)
		{
			sibling->isRed = false;
			node->parent->isRed = true;
			rightRotate(node->parent);
			sibling = node->parent->left;
		}
		if (not sibling->right->isRed and not sibling->left->isRed)
		{
			sibling->isRed = true;
			return node->parent;
		}
		else
		{
			if (not sibling->left->isRed)
			{
				sibling->right->isRed = false;
				sibling->isRed = true;
				leftRotate(sibling);
				sibling = node->parent->left;
			}
			sibling->isRed = node->parent->isRed;
			node->parent->isRed = false;
			sibling->left->isRed = false;
			rightRotate(node->parent);
			return root;
		}
	}

};

#endif //FT_CONTAINERS_BTREE_HPP
