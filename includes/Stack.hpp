/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <lsoulier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 23:44:23 by lsoulier          #+#    #+#             */
/*   Updated: 2021/03/01 23:44:24 by lsoulier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP
# include "List.hpp"

namespace ft {
	template<class T, class Container = List<T> >
	class Stack {
	public:
		/* Member types
		 *
		 *
		 */
		typedef Container container_type;
		typedef typename Container::value_type value_type;
		typedef typename Container::size_type size_type;
		typedef typename Container::reference reference;
		typedef typename Container::const_reference const_reference;

		/* Member functions
		 *
		 *
		 */
		Stack() {}
		Stack(const Stack& src) { *this = src; }
		Stack& operator=(const Stack& rhs) {
			if (this != &rhs)
				_c = rhs._c;
			return *this;
		}
		virtual ~Stack() {}

		/* Member functions : Element access
		 *
		 *
		 */
		reference top() { return _c.back(); }
		const_reference top() const { return _c.back(); }

		/* Member functions : Capacity
		 *
		 *
		 */
		bool empty() const { return _c.empty(); }
		size_type size() const { return _c.size(); }

		/* Member functions : Modifiers
		 *
		 *
		 */
		void push( const value_type& value ) { _c->push_back(value); }
		void pop() { _c->pop_back(); }
		void swap( Stack& other ) {	_c.swap(other._c); }

	private:
		Container _c;

		/* Non-member functions
		 *
		 *
		 */
		friend bool operator==( const Stack<T,Container>& lhs, const Stack<T,Container>& rhs ) {
			return lhs._c == rhs._c;
		}
		friend bool operator!=( const Stack<T,Container>& lhs, const Stack<T,Container>& rhs ) {
			return lhs._c != rhs._c;
		}
		friend bool operator<( const Stack<T,Container>& lhs, const Stack<T,Container>& rhs ) {
			return lhs._c < rhs._c;
		}
		friend bool operator<=( const Stack<T,Container>& lhs, const Stack<T,Container>& rhs ) {
			return lhs._c <= rhs._c;
		}
		friend bool operator>( const Stack<T,Container>& lhs, const Stack<T,Container>& rhs ) {
			return lhs._c > rhs._c;
		}
		friend bool operator>=( const Stack<T,Container>& lhs, const Stack<T,Container>& rhs ) {
			return lhs._c >= rhs._c;
		}

		void swap( Stack<T,Container>& lhs, Stack<T,Container>& rhs ) { lhs.swap(rhs); }

	};
}
#endif
