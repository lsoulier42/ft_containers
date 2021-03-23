/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <lsoulier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 23:44:23 by lsoulier          #+#    #+#             */
/*   Updated: 2021/03/01 23:44:24 by lsoulier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP
# include "list.hpp"

namespace ft {
	template<class T, class Container = list<T> >
	class stack {
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
		explicit stack( const Container& cont = Container() ) : _c(cont) {}
		stack(const stack& src) { *this = src; }
		stack& operator=(const stack& rhs) {
			if (this != &rhs)
				_c = rhs._c;
			return *this;
		}
		virtual ~stack() {}

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
		void push( const value_type& value ) { _c.push_back(value); }
		void pop() { _c.pop_back(); }
		void swap( stack& other ) {	_c.swap(other._c); }

	private:
		Container _c;

		/* Non-member functions
		 *
		 *
		 */
		friend bool operator==( const stack<T,Container>& lhs, const stack<T,Container>& rhs ) {
			return lhs._c == rhs._c;
		}
		friend bool operator!=( const stack<T,Container>& lhs, const stack<T,Container>& rhs ) {
			return lhs._c != rhs._c;
		}
		friend bool operator<( const stack<T,Container>& lhs, const stack<T,Container>& rhs ) {
			return lhs._c < rhs._c;
		}
		friend bool operator<=( const stack<T,Container>& lhs, const stack<T,Container>& rhs ) {
			return lhs._c <= rhs._c;
		}
		friend bool operator>( const stack<T,Container>& lhs, const stack<T,Container>& rhs ) {
			return lhs._c > rhs._c;
		}
		friend bool operator>=( const stack<T,Container>& lhs, const stack<T,Container>& rhs ) {
			return lhs._c >= rhs._c;
		}

		void swap( stack<T,Container>& lhs, stack<T,Container>& rhs ) { lhs.swap(rhs); }

	};
}
#endif
