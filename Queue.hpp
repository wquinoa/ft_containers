//
// Created by Filipp Ewseew on 2/22/21.
//

#ifndef FT_CONTAINERS_QUEUE_HPP
#define FT_CONTAINERS_QUEUE_HPP
# include "List/List.hpp"

namespace ft
{
    template <class T, class Container = ft::List<T> >
    class Queue
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
        explicit Queue(const Container &cont = Container()) : c(cont)
        {
        }

        Queue &operator= (const Queue &copy)
        {
            c = copy.c;
            return *this;
        }

        ~Queue()
        {
        }

        inline reference        front()         { return c.front(); }
        inline const_reference  front() const   { return c.front(); }
        inline reference        back()          { return c.back(); }
        inline const_reference  back() const    { return c.back(); }
        inline bool             empty() const   { return c.empty(); }
        inline size_type        size() const    { return c.size(); }

        inline void push(const reference val)   { return c.push_back(val); }
        inline void pop()                       { return c.pop_front(); }
        inline void swap(Queue &other)          { c.swap(other.c); }

        inline friend bool operator< (const Queue &lhs, const Queue &rhs) { return lhs.c < rhs.c; }
        inline friend bool operator> (const Queue &lhs, const Queue &rhs) { return rhs < lhs; }
        inline friend bool operator<=(const Queue &lhs, const Queue &rhs) { return not (rhs < lhs); }
        inline friend bool operator>=(const Queue &lhs, const Queue &rhs) { return not (lhs < rhs); }
        inline friend bool operator==(const Queue &lhs, const Queue &rhs) { return lhs.c == rhs.c; }
        inline friend bool operator!=(const Queue &lhs, const Queue &rhs) { return not (rhs == lhs); }
    };

    template< class T, class Container >
    void swap( ft::Queue<T,Container>& lhs, ft::Queue<T,Container>& rhs) { lhs.swap(rhs); }
}

#endif //FT_CONTAINERS_QUEUE_HPP
