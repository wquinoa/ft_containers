//
// Created by user on 31.01.2021.
//

// DAta structures https://www.youtube.com/watch?v=RBSGKlAvoiM

#ifndef FT_CONTAINERS_BTREE_HPP
# define FT_CONTAINERS_BTREE_HPP
# include <memory>
# include <iostream>
# include <vector>
# include <iomanip>

namespace shitty
{
	template <typename T>
	struct Comparator : public std::binary_function<T, T, bool>
	{
		bool operator() (const T &a, const T &b) const
		{
			return a < b;
		}
	};


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
			data = copy.data;
			isBlack = copy.isBlack;
			parent = copy.parent;
			left = copy.left;
			right = copy.right;
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

        bool isLeft()
		{
        	return (parent and parent->isLeft());
		}

		node *grandparent()
		{
        	if (this->parent)
				return this->parent->parent;
        	return nullptr;
		}

        node *getUncle()
		{
        	node *grandma;

        	if (parent == nullptr)
        		return nullptr;
        	if (parent->parent == nullptr)
				return nullptr;
        	grandma = parent->parent;
        	return parent->isLeft() ? grandma->right : grandma->left;
		}

		node *getSister()
		{
        	if (not parent)
				return nullptr;
        	if (this->isLeft())
				return parent->right;
			return parent->left;
		}

		// moves node down and moves given node in its place
		void moveDown(node *tmp)
		{
			if (this->parent)
			{
				if (isLeft())
					parent->left = tmp;
				else
					parent->right = tmp;
			}
			tmp->parent = parent;
			parent = tmp;
		}

		bool hasRedChild()
		{
			return (left and not left->isBlack) or (right and not right->isBlack);
		}

		~RBTreeNode() {}

    };

    template <typename T>
    bool operator<(RBTreeNode<T> a, RBTreeNode<T> b)
    { return a.data < b.data; }

    template <class Key, class Tp = Key, class Comp = shitty::Comparator<Key>,
            class Allocator = std::allocator<Key> >
    class RBTree
    {
        typedef RBTreeNode<Key>       	node_type;


        node_type   *root;
        size_t      size;
        Comp		Compare;


        void	leftrightRotate(node_type *node)
		{
        	leftRotate(node->left);
        	rightRotate(node);
		}

        void    rightleftRotate(node_type *node)
        {
			rightRotate(node->right);
			leftRotate(node);
        }

        void    leftRotate(node_type *node)
        {
			node_type *tmp = node->right;

			if (node == root)
				root = tmp;
			node->moveDown(tmp);
			node->right = tmp->left;
			if (tmp->left)
				tmp->left->parent = node;
			tmp->left = node;
		}

        void    rightRotate(node_type *node)
        {
			node_type *tmp = node->left;

			if (node == root)
				root = tmp;

			node->moveDown(tmp);
			node->left = tmp->right;
			if (tmp->right)
				tmp->right->parent = node;
			tmp->right = node;
		}

		void swapColors(node_type *x1, node_type *x2) {
			bool temp;
			temp = x1->isBlack;
			x1->isBlack = x2->isBlack;
			x2->isBlack = temp;
		}

		void fixDoubleRed(node_type *x)
		{

			if (x == root) {
				x->isBlack = true;
				return;
			}

			if (x->parent->isBlack)
				return;

			node_type *parent = x->parent;
			node_type *uncle = x->getUncle();
			node_type *grandparent = parent->parent;
			if (uncle != nullptr and uncle->isBlack == false)
			{
				// uncle red, perform recoloring and recurse
				parent->isBlack = true;
				uncle->isBlack = true;
				grandparent->isBlack = false;
				fixDoubleRed(grandparent);
			}
			else
			{
				if (parent->isLeft())
				{
					if (x->isLeft())
						swapColors(parent, grandparent);
					else
					{
						leftRotate(parent);
						swapColors(x, grandparent);
					}
					rightRotate(grandparent);
				}
				else
				{
					if (x->isLeft())
					{
						rightRotate(parent);
						swapColors(x, grandparent);
					}
					else
						swapColors(parent, grandparent);
					leftRotate(grandparent);
				}
			}
		}

        /* General utility */

		size_t height(node_type * node)
		{
			if (not node)
				return 0;

			size_t left = height(node->left);
			size_t right = height(node->right);

			return (std::max(left, right) + 1);
		}

	 public:
        RBTree() : root(), size()
        {
        	Compare = Comp();
        }

        bool    empty()
        {
            return (size == 0);
        }

        node_type *find(Key data)
		{
        	node_type *tmp = root;

        	while (tmp)
			{
        		if (Compare(data, tmp->data))
        		{
					if (not tmp->left)
						return tmp;
					else
						tmp = tmp->left;
				}
        		else if (Compare(tmp->data, data))
				{
        			if (not tmp->right)
        				return tmp;
        			else
        				tmp = tmp->right;
				}
        		else break ; // here tmp->data == given data
			}
        	return tmp;
		}

		void inorder(node_type *x) {
			if (x == NULL)
				return;
			inorder(x->left);
			std::cout << x->data << " ";
			inorder(x->right);
		}

		void    add(Key data)
        {
            if (size == 0)
            {
                root = new node_type(data);
                root->isBlack = true;
            }
            else
			{
            	node_type *tmp = find(data);
            	node_type *to_add;
            	if (tmp->data == data)
            		return ;

            	to_add = new node_type(data);
				if (Compare(data, tmp->data))
					tmp->left = to_add;
            	else
            		tmp->right = to_add;
            	to_add->parent = tmp;
            	fixDoubleRed(to_add);
			}
            size++;
        }

        /* General utility */

		void printLevelOrder()
		{
			int h = height(root);

			for (int i = 1; i <= h; i++)
				printGivenLevel(root, i);
		}

		void postorder(node_type* p, int indent = 0)
		{
			if(p != NULL)
			{
				if(p->right) {
					postorder(p->right, indent+4);
				}
				if (indent) {
					std::cout << std::setw(indent) << ' ';
				}
				if (p->right) std::cout << " /\n" << std::setw(indent) << ' ';
				std::cout << (p->isBlack ? "\033[30;1m" : "\033[31m") << p->data << "\033[0;m\n ";
				if(p->left) {
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
			if (root == nullptr)
				std::cout << "Tree is empty" << std::endl;
			else
				inorder(root);
			std::cout << std::endl;
		}
    };

};

#endif //FT_CONTAINERS_BTREE_HPP
