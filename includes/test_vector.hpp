/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_vector.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <lsoulier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 14:28:14 by lsoulier          #+#    #+#             */
/*   Updated: 2021/03/07 14:28:15 by lsoulier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_VECTOR_HPP
# define TEST_VECTOR_HPP
# include "vector.hpp"
# include <string>
# include <iostream>
# include "common.hpp"

void test_vector();
void test_vector_constructor(void);
void test_vector_pushpop_back(void);
void test_vector_assign(void);
void test_vector_frontback(void);
void test_vector_insert(void);
void test_vector_erase(void);
void test_vector_at(void);
void test_vector_operator_bracket(void);
void test_vector_clear(void);
void test_vector_max_size(void);
void test_vector_reserve(void);
void test_vector_resize(void);
void test_vector_iterator(void);
void test_vector_comparison(void);
void test_vector_swap(void);
#endif
