//
// Created by user on 04.02.2021.
//

#ifndef FT_CONTAINERS_ITERATOR_HPP
#define FT_CONTAINERS_ITERATOR_HPP

#include <cstddef>

/*
 * https://en.wikipedia.org/wiki/Substitution_failure_is_not_an_error
 */

namespace ft
{

	struct input_iterator_tag
	{
	};
	struct output_iterator_tag
	{
	};
	struct forward_iterator_tag : public input_iterator_tag
	{
	};
	struct bidirectional_iterator_tag : public forward_iterator_tag
	{
	};
	struct random_access_iterator_tag : public bidirectional_iterator_tag
	{
	};

	template<typename iterator>
	struct iterator_traits
	{
		typedef typename iterator::difference_type		difference_type;
		typedef typename iterator::value_type			value_type;
		typedef typename iterator::pointer				pointer;
		typedef typename iterator::reference			reference;
		typedef typename iterator::iterator_category	iterator_category;
	};

	template<typename T>
	struct iterator_traits<T *>
	{
		typedef ptrdiff_t					difference_type;
		typedef T							value_type;
		typedef T*							pointer;
		typedef T&							reference;
		typedef random_access_iterator_tag	iterator_category;
	};

	template<typename T>
	struct iterator_traits<const T *>
	{
		typedef ptrdiff_t					difference_type;
		typedef T							value_type;
		typedef const T*					pointer;
		typedef const T&					reference;
		typedef random_access_iterator_tag	iterator_category;
	};

	template <typename rit>
	class ReverseIterator
	{
	 public:
		typedef rit													iterator_type;
		typedef typename iterator_traits<rit>::difference_type		difference_type;
		typedef typename iterator_traits<rit>::value_type			value_type;
		typedef typename iterator_traits<rit>::pointer				pointer;
		typedef typename iterator_traits<rit>::reference				reference;
		typedef typename iterator_traits<rit>::iterator_category		iterator_category;

	 protected:
		iterator_type ptr;

	 public:
		const iterator_type &base() const
		{
			return ptr;
		};

		ReverseIterator() : ptr() {};

		ReverseIterator(iterator_type copy) : ptr(copy)
		{
		}

		ReverseIterator(const ReverseIterator<rit> &copy) : ptr(copy.ptr)
		{
		}

		~ReverseIterator()
		{
		}


		ReverseIterator<rit> &operator= (const ReverseIterator<rit> &other)
		{
			ptr = other.ptr;
			return *this;
		}

		ReverseIterator<rit> &operator++ ()
		{
			--ptr;
			return *this;
		}

		ReverseIterator<rit> operator++ (int)
		{
			ReverseIterator<rit> old(*this);
			--ptr;
			return old;
		}

		reference operator* () const
		{
			return ptr.get_ptr()->data;
		}

		pointer operator-> () const
		{
			return &operator* ();
		}

		ReverseIterator<rit> &operator-- ()
		{
			++ptr;
			return *this;
		}

		ReverseIterator<rit> operator-- (int)
		{
			ReverseIterator<rit> old(*this);

			++ptr;
			return old;
		}
	};

	/*
	 * http://mit.spbau.ru/sewiki/images/7/72/Lect10.pdf
	 */

	template < bool ASS, class T = void >
	struct enable_if {};

	template < class T >
	struct enable_if <true, T > {
		typedef T type ;
	};

//	template <class T, class = void>
//	struct has_iterator_typedefs
//	{
//		static T makeT();
//
//		static char test(...);
//
//		template <typename U,
//				typename=typename ft::iterator_traits<U>::difference_type,
//				typename=typename ft::iterator_traits<U>::pointer,
//				typename=typename ft::iterator_traits<U>::reference,
//				typename=typename ft::iterator_traits<U>::value_type,
//				typename=typename ft::iterator_traits<U>::iterator_category
//		> static long test(U);
//
//		static const bool value = sizeof(test(makeT())) == sizeof(long);
//	};

	/*template <typename T>
	struct has_iterator_typedefs
	{
		static T makeT();
		typedef void * twoptrs[2];  // sizeof(twoptrs) > sizeof(void *)
		static twoptrs & test(...); // Common case
		template<class R> static typename R::iterator_category * test(R); // Iterator
		template<class R> static void * test(R *); // Pointer

		static const bool value = sizeof(test(makeT())) == sizeof(void *);
	};*/

	template <typename T>
	struct has_iterator_category
	{
		template<class U>
		static short	test(...) {};

		template<class U>
		static char		test(typename U::iterator_category * = 0) {};

	 public:
		static const bool value = (sizeof(test<T>(0)) == sizeof(char));
	};

	template <typename IteratorL, typename IteratorR>
	inline bool operator== (const ReverseIterator<IteratorL>& lhs, const ReverseIterator<IteratorR>& rhs) {
		return (lhs.base() == rhs.base());
	}


	template <typename IteratorL, typename IteratorR>
	inline bool operator!= (const ReverseIterator<IteratorL>& lhs, const ReverseIterator<IteratorR>& rhs) {
		return !(lhs == rhs);
	}


	template< class InputIt >
	typename iterator_traits<InputIt>::difference_type
	distance(InputIt first, InputIt last, ft::input_iterator_tag)
	{
		typename InputIt::difference_type d;

		for (d = 0; first != last; ++first)
			++d;
		return d;
	}

};

#endif //FT_CONTAINERS_ITERATOR_HPP
