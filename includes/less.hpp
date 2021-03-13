/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   less.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louise <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 11:32:48 by louise            #+#    #+#             */
/*   Updated: 2021/03/13 11:32:49 by louise           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LESS_HPP
# define LESS_HPP

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
}

#endif
