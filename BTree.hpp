//
// Created by user on 31.01.2021.
//

// DAta structures https://www.youtube.com/watch?v=RBSGKlAvoiM

#ifndef FT_CONTAINERS_BTREE_HPP
# define FT_CONTAINERS_BTREE_HPP
# include <memory>
# include <iostream>
# include "Algorithm.hpp"

# include <iomanip>

namespace ft
{
    template <typename T>
    struct RBTreeNode
    {
#define N_RED false
#define N_BLACK true
        typedef T          	value_type;
        typedef RBTreeNode  node;

        value_type          data;
        bool                isBlack;
        node                *parent;
        node                *left;
        node                *right;

        /* Constructors */

        RBTreeNode()
        : data(), isBlack(), parent(), left(), right()
        {
        }

        RBTreeNode(const node &copy)
        {
			operator=(copy);
        }

        RBTreeNode(const T &data)
        : data(data), isBlack(), parent(), left(), right()
        {}

        node &operator=(const node &copy)
        {
            if (this != &copy)
            {
                data = copy.data;
                isBlack = copy.isBlack;
                parent = copy.parent;
                left = copy.left;
                right = copy.right;
            }
            return (*this);
        }

		~RBTreeNode()
		{
		}

		RBTreeNode *getSibling()
		{
        	if (this == parent->left)
        		return parent->right;
			else
				return parent->left;
		}

		bool 	hasRedChild()
		{
			return (right->isBlack or not left->isBlack);
		}

    };

    template <typename T>
    bool operator<(RBTreeNode<T> a, RBTreeNode<T> b)
    { return a.data < b.data; }

    template <class Key, class Tp = Key, class Comp = ft::less<Key>,
            class Allocator = std::allocator<Tp>, bool isUnique = true >
    class RBTree
    {
        typedef RBTreeNode<Key>       	node_type;

        node_type  			*root;
        node_type 			*_endptr;
        size_t      		size;
        Comp				Compare;

        node_type *minvalue(node_type *node)
		{
        	node_type *tmp = node;

			while (tmp->left != _endptr)
				tmp = tmp->left;

			return tmp;
		}
        
        void    leftRotate(node_type *node)
        {
			node_type *tmp = node->right;

			node->right = tmp->left;
			if (tmp->left != _endptr)
				tmp->left->parent = node;
			tmp->parent = node->parent;
			if (node->parent == _endptr)
				root = tmp;
			else if (node->parent->left == node)
				node->parent->left = tmp;
			else
				node->parent->right = tmp;
			tmp->left = node;
			node->parent = tmp;
		}

        void    rightRotate(node_type *node)
        {
			node_type *tmp = node->left;

			node->left = tmp->right;
			if (tmp->right != _endptr)
				tmp->right->parent = node;
			tmp->parent = node->parent;
			if (node->parent == _endptr)
				root = tmp;
			else if (node->parent->left == node)
				node->parent->left = tmp;
			else
				node->parent->right = tmp;
			tmp->right = node;
			node->parent = tmp;
		}

		void fixDoubleRed(node_type *node)
		{
        	if (node->parent == _endptr)
				return ;

        	node_type *parent = node->parent;
        	node_type *grandparent = parent->parent;
        	node_type *uncle = (parent == grandparent->left) ? grandparent->right : grandparent->left;

        	if (parent->isBlack == false)
			{
        		if (not uncle->isBlack)
				{
        			parent->isBlack = true;
        			uncle->isBlack = true;
        			grandparent->isBlack = false;
        			fixDoubleRed(node);
				}
        		else
				{
        			if (parent == grandparent->left)
					{
        				if (node == parent->left)
        					swap(parent->isBlack, grandparent->isBlack);
        				else
						{
        					leftRotate(parent);
        					swap(node->isBlack, grandparent->isBlack);
						}
        				rightRotate(grandparent);
					}
        			else
					{
        				if (node == parent->right)
							swap(parent->isBlack, grandparent->isBlack);
						else
						{
							rightRotate(parent);
							swap(node->isBlack, grandparent->isBlack);
						}
						leftRotate(grandparent);
					}
				}
			}
		}

		void 	fixDoubleBlack(node_type *node)
		{
        	_endptr->isBlack = true;
        	if (node->parent == _endptr)
				return ;

        	node_type *sibling = node->getSibling();
        	node_type *parent = node->parent;

        	if (sibling == _endptr)
			{
        		fixDoubleBlack(parent);
			}
        	else
        	{
				if (not sibling->isBlack)
				{
					parent->isBlack = false;
					sibling->isBlack = true;
					if (sibling == sibling->parent->left)
					{
						rightRotate(parent);
					}
					else
					{
						leftRotate(parent);
					}
					fixDoubleBlack(node);
				}
				else
				{
					if (sibling->hasRedChild())
					{
						if (not sibling->left->isBlack)
						{
							if (sibling == sibling->parent->left)
							{
								sibling->left->isBlack = sibling->isBlack;
								sibling->isBlack = parent->isBlack;
								rightRotate(parent);
							}
							else
							{
								sibling->left->isBlack = parent->isBlack;
								rightRotate(sibling);
								leftRotate(parent);
							}
						}
						else
						{
							if (sibling == sibling->parent->right)
							{
								sibling->right->isBlack = sibling->isBlack;
								sibling->isBlack = parent->isBlack;
								leftRotate(parent);
							}
							else
							{
								sibling->right->isBlack = parent->isBlack;
								leftRotate(sibling);
								rightRotate(parent);
							}
						}
						parent->isBlack = true;
					}
					else
					{
						sibling->isBlack = false;
						if (parent->isBlack)
							fixDoubleBlack(parent);
						else
							parent->isBlack = true;
					}
				}
			}
		}

		void 	del(node_type *node)
		{
			node_type *parent = node->parent;
			node_type *u;
			bool		doubleBlack;

			if (node->left != _endptr and node->right != _endptr)
				u = minvalue(node->right);
			else if (node->left == _endptr and node->right == _endptr)
				u = _endptr;
			else if (node->left != _endptr)
				u = node->left;
			else
				u = node->right;
			doubleBlack = (u == _endptr or u->isBlack) and (node->isBlack);

			if (u == _endptr)
			{
				if (node->parent == _endptr)
				{
					root = _endptr;
				}
				else
				{
					if (doubleBlack)
					{
						fixDoubleBlack(node);
					}
					else
					{
						if (node->getSibling() != _endptr)
							node->getSibling()->isBlack = false;
					}
					if (node == node->parent->left)
					{
						parent->left = _endptr;
					}
					else
					{
						parent->right = _endptr;
					}
				}
				delete node;
				return ;
			}

			if (node->left == _endptr or node->right == _endptr)
			{
				if (node->parent == _endptr)
				{
					node->data = u->data;
					node->left = node->right = _endptr;
					delete u;
				}
				else
				{
					if (node == node->parent->right)
						parent->right = u;
					else
						parent->left = u;
					delete node;
					u->parent = parent;

					if (doubleBlack)
					{
						fixDoubleBlack(u);
					}
					else
					{
						u->isBlack = true;
					}
				}
				return ;
			}

			// two black children
			swap(node->data, u->data);
			del(u);
			_endptr->isBlack = true;
		}

		node_type *createEmptyNode()
		{
			node_type *rv = new node_type();

			rv->left = _endptr;
			rv->right = _endptr;
			rv->parent = _endptr;
			rv->isBlack = false;

			return rv;
		};

	 public:
		RBTree() : size()
		{
			_endptr = createEmptyNode();

			_endptr->isBlack = true;
			root = _endptr;
        }

        bool    empty()
        {
            return (size == 0);
        }

        node_type *find(Key data)
		{
        	node_type *tmp = root;

        	while (tmp != _endptr)
			{
        		if (Compare(data, tmp->data))
					tmp = tmp->left;
        		else if (Compare(tmp->data, data))
       				tmp = tmp->right;
        		else break;// here tmp->data == given data
			}
        	return tmp;
		}

		void inorder(node_type *x) {
			if (x == _endptr)
				return;
			inorder(x->left);
			std::cout << x->data << " ";
			inorder(x->right);
		}

		typename ft::enable_if<isUnique, void>::type
		add(Key data)
        {
        	if (size == 0)
			{
        		root = createEmptyNode();
        		root->isBlack = true;
        		root->data = data;
        		//_endptr->parent = root;
			}
        	else
        	{
				node_type *tmp = root;
				node_type *newparent;

				while (tmp != _endptr)
				{
					newparent = tmp;
					if (Compare(data, tmp->data))
						tmp = tmp->left;
					else if (Compare(tmp->data, data))
						tmp = tmp->right;
					else return ;
				}

				node_type *baby = createEmptyNode();

				baby->data = data;
				baby->parent = newparent;
				if (Compare(baby->data, newparent->data))
					newparent->left = baby;
				else
					newparent->right = baby;

				if (newparent->parent != _endptr)
					fixDoubleRed(baby);
				root->isBlack = _endptr->isBlack = true;
			}
            size++;
		}

		void	delVal(Key key)
		{
			node_type *node = find(key);
			if (node == _endptr)
				return ;
			del(node);
		}


		/* General utility */

		void postorder(node_type* p, int indent = 0)
		{
			if(p != _endptr)
			{
				if(p->right != _endptr) {
					postorder(p->right, indent+4);
				}
				if (indent) {
					std::cout << std::setw(indent) << ' ';
				}
				if (p->right != _endptr) std::cout << " /\n" << std::setw(indent) << ' ';
				std::cout << (p->isBlack ? "\033[30;1m" : "\033[31m") << p->data << "\033[0;m\n ";
				if(p->left != _endptr) {
					std::cout << std::setw(indent) << ' ' <<" \\\n";
					postorder(p->left, indent+4);
				}
			}
		}

		void 	prettyprint()
		{
			std::vector<std::string> matrix;

			postorder(root);
		}

		void printInOrder() {
			std::cout << "Inorder: " << std::endl;
			if (root == _endptr)
				std::cout << "Tree is empty" << std::endl;
			else
				inorder(root);
			std::cout << std::endl;
		}
    };

};

#endif //FT_CONTAINERS_BTREE_HPP
