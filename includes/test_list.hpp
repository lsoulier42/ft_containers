/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_list.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <lsoulier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 11:07:11 by lsoulier          #+#    #+#             */
/*   Updated: 2021/03/01 18:34:17 by lsoulier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_LIST_HPP
# define TEST_LIST_HPP
# include "List.hpp"
# include "common.hpp"
# include <iostream>
# include <cstdlib>
# include <ctime>
# define ARRAY_SIZE 5
# ifdef __linux__
#  include <climits>
# endif
# ifdef __apple__
#  include <limits>
# endif

void test_list(void);
void test_list_int(void);
void print_list(ft::List<int> & current_list);
void create_int_container(ft::List<int> *container_ptr);
void test_list_int_push_back(void);
void test_list_int_size(void);
void test_list_int_pop_back(void);
void test_list_int_clear(void);
void test_list_int_push_front(void);
void test_list_int_pop_front(void);
void test_list_int_assign(void);
void test_list_int_front(void);
void test_list_int_back(void);
void test_list_int_resize(void);
void test_list_int_remove(void);
void test_list_int_swap(void);
void test_list_int_merge(void);
void test_list_int_reverse();
void test_list_int_unique(void);
void test_list_int_operator(void);
void test_list_int_iterator(void);
void test_list_int_insert(void);

#endif
