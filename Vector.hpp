//
// Created by Filipp Ewseew on 1/30/21.
//

#ifndef FT_CONTAINERS__VECTOR_HPP_
# define FT_CONTAINERS__VECTOR_HPP_
# include <iostream>
# include <memory>
# include <vector>

template <class T, class Allocator = std::allocator<T> >
class Vector
{
 private:
	typedef Allocator                                allocator_type;
	typedef allocator_traits<allocator_type>         __alloc_traits;
	typedef typename __alloc_traits::size_type       size_type;

 protected:
	typedef T                                        value_type;
	typedef value_type&                              reference;
	typedef const value_type&                        const_reference;
	typedef typename __alloc_traits::difference_type difference_type;
	typedef typename __alloc_traits::pointer         pointer;
	typedef typename __alloc_traits::const_pointer   const_pointer;
	typedef pointer                                  iterator;
	typedef const_pointer                            const_iterator;

	pointer     _begin;
	pointer     _end;
	size_type   size;
	allocator_type &_alloc;

 public:
	inline explicit Vector(allocator type const& a = allocator_type()) {};
	inline explicit Vector(size_type n, value_type &val = value_type()
						const allocator_type &alloc = allocator_type()) {};

	//template<class InputIterator>
	//Vector(InputIterator first, InputIterator last,
		//const allocator_type &alloc = allocator_type()) {};

	Vector(const Vector &x) {
		_alloc.deallocate(_begin);
	}
};


#endif //FT_CONTAINERS__VECTOR_HPP_
