//
// Created by user on 04.02.2021.
//

#ifndef FT_CONTAINERS_ITERATOR_HPP
#define FT_CONTAINERS_ITERATOR_HPP

#include <cstddef>

/*
 * https://en.wikipedia.org/wiki/Substitution_failure_is_not_an_error
 */

namespace shitty
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
	struct IteratorTraits
	{
		typedef typename iterator::difference_type		difference_type;
		typedef typename iterator::value_type			value_type;
		typedef typename iterator::pointer				pointer;
		typedef typename iterator::reference			reference;
		typedef typename iterator::iterator_category	iterator_category;
	};

	template<typename T>
	struct IteratorTraits<T *>
	{
		typedef ptrdiff_t					difference_type;
		typedef T							value_type;
		typedef T*							pointer;
		typedef T&							reference;
		typedef random_access_iterator_tag	iterator_category;
	};

	template<typename T>
	struct IteratorTraits<const T *>
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
		typedef typename IteratorTraits<rit>::difference_type		difference_type;
		typedef typename IteratorTraits<rit>::value_type			value_type;
		typedef typename IteratorTraits<rit>::pointer				pointer;
		typedef typename IteratorTraits<rit>::reference				reference;
		typedef typename IteratorTraits<rit>::iterator_category		iterator_category;

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
			return *ptr;
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

	template <typename T>
	struct has_iterator_typedefs
	{
		typedef char yes[1];
		typedef char no[2];

		/* Return "no" if typedefs are absent */
		template <typename>
		static no& test(...) {};

		/* Return "yes" C has the typedefs */
		template<typename C>
		static yes &test(
				typename C::iterator_category * = nullptr,
				typename C::difference_type * = nullptr,
				typename C::value_type * = nullptr,
				typename C::reference * = nullptr,
				typename C::pointer * = nullptr
				) {};

		/* True if test returns "yes" */
		static const bool value = (sizeof(test<T>()) == sizeof(yes));
	};

	template<typename It>
	size_t distance(It from, It to)
	{
		ptrdiff_t dist;

		for (dist = 0; from != to; ++from)
			++dist;
		return dist;
	}

	template <typename IteratorL, typename IteratorR>
	inline bool operator== (const ReverseIterator<IteratorL>& lhs, const ReverseIterator<IteratorR>& rhs) {
		return (lhs.base() == rhs.base());
	}


	template <typename IteratorL, typename IteratorR>
	inline bool operator!= (const ReverseIterator<IteratorL>& lhs, const ReverseIterator<IteratorR>& rhs) {
		return !(lhs == rhs);
	}

};

#endif //FT_CONTAINERS_ITERATOR_HPP
