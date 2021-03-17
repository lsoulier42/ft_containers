/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louise <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 10:45:27 by louise            #+#    #+#             */
/*   Updated: 2021/03/13 10:45:28 by louise           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAIR_HPP
# define PAIR_HPP

namespace ft {
    template<class T1, class T2>
    struct pair {
        typedef T1 first_type;
        typedef T2 second_type;
        T1 first;
        T2 second;

        pair();
        pair( const T1& x, const T2& y );
        pair( const pair& p );
        pair& operator=( const pair& other );
    };

	template<class T1, class T2>
	pair<T1, T2>::pair() {}

	template<class T1, class T2>
	pair<T1, T2>::pair( const T1& x, const T2& y ) : first(x), second(y) {}

	template< class T1, class T2>
	pair<T1, T2>::pair( const pair& p ) { *this = p; }

	template< class T1, class T2>
	pair<T1, T2>& pair<T1, T2>::operator=( const pair& other ) {
		if (this != &other) {
			first = other.first;
			second = other.second;
		}
		return *this;
	}

    template< class T1, class T2 >
    pair<T1,T2> make_pair( T1 t, T2 u ) {
        return pair<T1, T2>(t, u);
    }

    template< class T1, class T2 >
    bool operator==( const pair<T1,T2>& lhs, const pair<T1,T2>& rhs ) {
        return (lhs.first == rhs.first && lhs.second == rhs.second);
    }
    template< class T1, class T2 >
    bool operator!=( const pair<T1,T2>& lhs, const pair<T1,T2>& rhs ) {
        return !(lhs == rhs);
    }
    template< class T1, class T2 >
    bool operator<( const pair<T1,T2>& lhs, const pair<T1,T2>& rhs ) {
        return (lhs.first < rhs.first || (lhs.first == rhs.first && lhs.second < rhs.second));
    }
    template< class T1, class T2 >
    bool operator<=( const pair<T1,T2>& lhs, const pair<T1,T2>& rhs ) {
        return (lhs < rhs || lhs == rhs);
    }
    template< class T1, class T2 >
    bool operator>( const pair<T1,T2>& lhs, const pair<T1,T2>& rhs ) {
        return (!(lhs < rhs) && lhs != rhs);
    }
    template< class T1, class T2 >
    bool operator>=( const pair<T1,T2>& lhs, const pair<T1,T2>& rhs ) {
        return !(lhs < rhs);
    }
}

#endif
