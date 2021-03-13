/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louise <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 10:33:49 by louise            #+#    #+#             */
/*   Updated: 2021/03/13 10:33:50 by louise           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP
# include <memory>
# include <iostream>
# include "iterator"
# include "enable_if.hpp"
# include "pair.hpp"
# include "less.hpp"

namespace ft {
    template< class Key, class T,
        class Compare = ft::less<Key>,
        class Allocator = std::allocator<ft::pair<const Key, T> >
    > class Map {
    public:

        /* Member types
         *
         *
         *
         */
        typedef Key key_type;
        typedef T mapped_type;
        typedef ft::pair<const Key, T> value_type;
        typedef std::size_t size_type;
        typedef std::ptrdiff_t difference_type;
        typedef Compare key_compare;
        


    private:

    };

}

#endif
