//
// Created by user on 21.02.2021.
//

#ifndef FT_CONTAINERS_RBNODE_HPP
#define FT_CONTAINERS_RBNODE_HPP

namespace ft
{
	template<typename T, class C>
	class RBNode
	{
	 public:

		T data;
		RBNode *parent;
		RBNode *left;
		RBNode *right;
		bool isBlack;

		explicit RBNode(T const &val = T(), bool isBlackk = false) : data(val), parent(), left(), right(),
																	 isBlack(isBlackk)
		{
		}

		RBNode(const RBNode &copy) : data(copy.data), parent(copy.parent), left(copy.left), right(copy.right),
									 isBlack(false)
		{
		}

		RBNode &operator=(const RBNode &copy)
		{
			if (this != &copy) {
				data = copy.data;
				parent = copy.parent;
				left = copy.left;
				right = copy.right;
				isBlack = copy.isBlack;
			}
			return *this;
		}

		~RBNode()
		{
		}

		bool operator>(const RBNode &other)
		{ return C()(other.data, data); }

		bool operator<(const RBNode &other)
		{ return C()(data, other.data); }

		bool operator<=(const RBNode &other)
		{ return not(data > other.data); }

		bool operator>=(const RBNode &other)
		{ return not(data < other.data); }

		bool operator!=(const RBNode &other)
		{ return (data > other.data or data < other.data); }

		bool operator==(const RBNode &other)
		{ return not(data != other.data); }

		bool isLeft()
		{ return this == parent->left; }

		RBNode *nextn();

		RBNode *prevn();

	 private:
		void setEnds();

		RBNode *root;
		RBNode *first;
		RBNode *last;

	};

	template<typename T, class C>
	void RBNode<T, C>::setEnds()
	{
		RBNode *tmp(this);

		while (tmp->parent)
			tmp = tmp->parent;
		root = tmp;

		while (tmp->left)
			tmp = tmp->left;
		first = tmp;

		tmp = root;
		while (tmp->right)
			tmp = tmp->right;
		last = tmp;
	}

	template<typename T, class C>
	RBNode<T, C> *RBNode<T, C>::prevn()
	{
		setEnds();
		if (this == first || this == last)
			return parent;
		RBNode *it(this);

		if (it->left)
		{
			it = it->left;
			while (it->right) it = it->right;
		}
		else
		{
			while (it->data >= data)
				it = it->parent;
		}
		return (it);
	}

	template<typename T, class C>
	RBNode<T, C> *RBNode<T, C>::nextn()
	{
		RBNode *it(this);

		if (it->right)
		{
			it = it->right;
			while (it->left) it = it->left;
		}
		else
		{
			RBNode *tmp = it;

			it = it->parent;
			while (it->left != tmp)
			{
				tmp = it;
				it = it->parent;
			}
		}
		return (it);
	}
}
#endif //FT_CONTAINERS_RBNODE_HPP
