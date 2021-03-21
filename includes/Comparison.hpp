/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comparison.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <lsoulier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 19:06:50 by lsoulier          #+#    #+#             */
/*   Updated: 2021/03/21 19:06:55 by lsoulier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMPARISON_HPP
# define COMPARISON_HPP

namespace ft {
	template< class T >
	struct less {
		typedef bool result_type;
		typedef T first_argument_type;
		typedef T second_argument_type;

		bool operator()( const T& lhs, const T& rhs ) const {
			return lhs < rhs;
		}
	};

	template< class T >
	struct equal_to {
		typedef bool result_type;
		typedef T first_argument_type;
		typedef T second_argument_type;

		bool operator()( const T& lhs, const T& rhs ) const {
			return lhs == rhs;
		}
	};

	template< class T >
	struct equal_to_unary {
		typedef bool result_type;
		typedef T first_argument_type;
		typedef T second_argument_type;

		explicit equal_to_unary(const T& ref) : _ref(ref) {}

		bool operator()(const T& other) const {
			return other == _ref;
		}

		const T& _ref;
	};

	template< class InputIt1, class InputIt2 >
	bool lexicographical_compare( InputIt1 first1, InputIt1 last1,
		InputIt2 first2, InputIt2 last2 ) {
		while(first1 != last1 && first2 != last2) {
			if (*first2 < *first1)
				return false;
			if (*first1 < *first2)
				return true;
			first1++;
			first2++;
		}
		return first1 == last1 && first2 != last2;
	}

	template< class InputIt1, class InputIt2, class Compare >
	bool lexicographical_compare( InputIt1 first1, InputIt1 last1,
		InputIt2 first2, InputIt2 last2, Compare comp ) {
		while(first1 != last1 && first2 != last2) {
			if (comp(*first2, *first1))
				return false;
			if (comp(*first1, *first2))
				return true;
			first1++;
			first2++;
		}
		return first1 == last1 && first2 != last2;
	}

	template< class InputIt1, class InputIt2 >
	bool equal( InputIt1 first1, InputIt1 last1,
		InputIt2 first2, InputIt2 last2 ) {
		while(first1 != last1 && first2 != last2) {
			if (*first1 != *first2)
				return false;
			first1++;
			first2++;
		}
		return first1 == last1 && first2 == last2;
	}
	template< class InputIt1, class InputIt2, class BinaryPredicate >
	bool equal( InputIt1 first1, InputIt1 last1,
				InputIt2 first2, InputIt2 last2, BinaryPredicate p ) {
		while(first1 != last1 && first2 != last2) {
			if (!p(*first1, *first2))
				return false;
			first1++;
			first2++;
		}
		return first1 == last1 && first2 == last2;
	}
}

#endif
