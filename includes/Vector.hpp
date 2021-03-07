/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <lsoulier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 14:26:37 by lsoulier          #+#    #+#             */
/*   Updated: 2021/03/07 14:26:38 by lsoulier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP
# include <limits>
# include <memory>
# include <iostream>
# include "enable_if.hpp"

namespace ft {
	template<class T, class Allocator = std::allocator<T> >
	class Vector {
	public:
		/* Member types
		 *
		 *
		 *
		 */
		typedef T value_type;
		typedef Allocator allocator_type;
		typedef std::size_t size_type;
		typedef std::ptrdiff_t difference_type;
		typedef typename Allocator::reference reference;
		typedef typename Allocator::const_reference const_reference;
		typedef typename Allocator::pointer pointer;
		typedef typename Allocator::const_pointer const_pointer;

		/* Iterator classes
		 *
		 *
		 *
		 *
		 */

		 class const_iterator;
		 class iterator;
		 class const_reverse_iterator;
		 class reverse_iterator;

		 /* Member functions : constructors
		  *
		  *
		  *
		  */
		 Vector() {

		 }
		 explicit Vector( const Allocator& alloc ) {

		 }
		 explicit Vector( size_type count,
			const T& value = T(), const Allocator& alloc = Allocator()) {

		 }
		template< class InputIt >
		Vector( InputIt first, InputIt last, const Allocator& alloc = Allocator() ) {

		 }
		Vector( const Vector& other ) {

		 }


	private:
		/* Private attributes
		 * _size is the number of current element in the array
		 * _capacity is the number of T already allocated
		 * _vla is the array that is going to grow if _size == _capacity
		 *
		 *
		 */
		allocator_type _a;
		pointer* _vla;
		size_type _size;
		size_type _capacity;

	};
}
#endif
