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
        {}

        RBTreeNode(const node &copy)
        {
			operator=();
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

		~RBTreeNode() {}

    };

    template <typename T>
    bool operator<(RBTreeNode<T> a, RBTreeNode<T> b)
    { return a.data < b.data; }

    template <class Key, class Tp = Key, class Comp = ft::less<Key>,
            class Allocator = std::allocator<Tp>, bool isUnique = true >
    class RBTree
    {
        typedef RBTreeNode<Key>       	node_type;

        node_type   *root, *_endptr;
        size_t      size;
        Comp		Compare;

        
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

//		void fixDoubleRed(node_type *node)
//		{
//        	node_type *uncle;
//        	node_type *grandparent;
//
//			while (not node->parent->isBlack)
//			{
//				grandparent = node->parent->parent;
//				/* root is always black and doesnt have a grandparent */
//				if (node->parent == grandparent->left)
//				{
//					uncle = grandparent->right;
//					if (uncle->isBlack)
//					{
//						node->parent->isBlack = true;
//						uncle->isBlack = true;
//						grandparent->isBlack = false;
//					}
//					else
//					{
//						if (node == node->parent->right)
//						{
//							node = node->parent;
//							leftRotate(node);
//						}
//
//						node->parent->isBlack = true;
//						node->parent->parent->isBlack = false;
//						rightRotate(node->parent->parent);
//					}
//				}
//				else
//				{
//					uncle = grandparent->left;
//					if (uncle->isBlack)
//					{
//						node->parent->isBlack = true;
//						uncle->isBlack = true;
//						grandparent->isBlack = false;
//					}
//					else
//					{
//						if (node == node->parent->left)
//						{
//							node = node->parent;
//							rightRotate(node);
//						}
//
//						node->parent->isBlack = true;
//						node->parent->parent->isBlack = false;
//						leftRotate(node->parent);
//					}
//				}
//			}
//			root->isBlack = true;
//		}

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
			root = _endptr = createEmptyNode();

			_endptr->isBlack = true;
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
				root->isBlack = true;
			}
            size++;
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
