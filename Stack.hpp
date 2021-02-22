//
// Created by Filipp Ewseew on 2/22/21.
//

#ifndef FT_CONTAINERS_STACK_HPP
#define FT_CONTAINERS_STACK_HPP
# include "Vector.hpp"

namespace ft
{
    template <class T, class Container = ft::Vector<T> >
    class Stack
    {
    public:
        typedef Container       container_type;
        using typename Container::value_type;
        using typename Container::size_type;
        using typename Container::reference;
        using typename Container::const_reference;

    protected:
        container_type c;

    public:
        explicit Stack(const Container &cont = Container()) : c(cont)
        {
        }

        Stack &operator= (const Stack &copy)
        {
            c = copy.c;
            return *this;
        }

        ~Stack()
        {
        }

        inline reference        top()           { return c.back(); }
        inline const_reference  top() const     { return c.back(); }
        inline bool             empty() const   { return c.empty(); }
        inline size_type        size() const    { return c.size(); }

        inline void push(const reference val)   { return c.push_back(val); }
        inline void pop()                       { return c.pop_back(); }
        inline void swap(Stack &other)          { c.swap(other.c); }

        friend bool operator< (const Stack &lhs, const Stack &rhs) { return lhs.c < rhs.c; }
        friend bool operator> (const Stack &lhs, const Stack &rhs) { return rhs < lhs; }
        friend bool operator<=(const Stack &lhs, const Stack &rhs) { return not (rhs < lhs); }
        friend bool operator>=(const Stack &lhs, const Stack &rhs) { return not (lhs < rhs); }
        friend bool operator==(const Stack &lhs, const Stack &rhs) { return lhs.c == rhs.c; }
        friend bool operator!=(const Stack &lhs, const Stack &rhs) { return not (rhs == lhs); }
    };

    template< class T, class Container >
    void swap( ft::Stack<T,Container>& lhs, ft::Stack<T,Container>& rhs)
    {
        lhs.swap(rhs);
    }
}

#endif //FT_CONTAINERS_STACK_HPP
