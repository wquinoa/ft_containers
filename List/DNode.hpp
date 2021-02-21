//
// Created by user on 05.02.2021.
//

#ifndef FT_CONTAINERS_DNODE_HPP
#define FT_CONTAINERS_DNODE_HPP

namespace ft
{
	template <class T>
	struct DNode
	{
		T		data;
		DNode	*next;
		DNode	*prev;

		DNode() : data(), next(), prev()
		{
		}

		DNode(T data) : data(data), next(), prev()
		{
		}

		~DNode()
		{
		}

		DNode(DNode const &copy)
		: data(copy.data), next(copy.next), prev(copy.prev)
		{
		}

		DNode &operator= (DNode const &copy)
		{
			if (this != &copy)
			{
				data = copy.data;
				next = copy.next;
				prev = copy.prev;
			}
		}

		DNode	*nextn() { return next; }
		DNode	*prevn() { return prev; }

		bool operator== (const DNode &rhs) const { return data == rhs.data; }
		bool operator!= (const DNode &rhs) const { return !(rhs == *this); }
		bool operator<(const DNode &rhs) const { return data < rhs.data; }
		bool operator>(const DNode &rhs) const { return rhs < *this; }
		bool operator<=(const DNode &rhs) const { return !(rhs < *this); }
		bool operator>=(const DNode &rhs) const { return !(*this < rhs); }
	};
}

#endif //FT_CONTAINERS_DNODE_HPP
