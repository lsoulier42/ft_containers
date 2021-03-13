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

        /* Member types
         *
         *
         */
        typedef T1 first_type;
        typedef T2 second_type;

        /* Member objects
         *
         *
         */
        T1 first;
        T2 second;

        /* member functions : constructors
         *
         *
         */

        pair() {}
        pair( const T1& x, const T2& y ) : first(x), second(y) {}
        template< class U1, class U2 >
        pair( const pair<U1, U2>& p ) { *this = src; }

        /* member functions : assignation operator
         *
         *
         */
        pair& operator=( const pair& other ) {
            if (this != &other) {
                first = other.first;
                second = other.second;
            }
            return *this;
        }
    };
    /* Non-member functions : make_pair
     * Creates a ft::pair object, deducing the target type from the types of arguments.
     *
     */
    template< class T1, class T2 >
    pair<T1,T2> make_pair( T1 t, T2 u ) {
        return pair(t, u);
    }

    /* Non-member functions : operator overloads
     *
     *
     */

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
        return (lhs.first < rhs.first || (lhs.first == rhs.first && lhs.second < rhs.second);
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
