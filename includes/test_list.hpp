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
# include "list.hpp"
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
void print_list(ft::list<int> & current_list);
void create_int_container(ft::list<int> *container_ptr);
void test_list_push_back(void);
void test_list_size(void);
void test_list_pop_back(void);
void test_list_clear(void);
void test_list_push_front(void);
void test_list_pop_front(void);
void test_list_assign(void);
void test_list_front(void);
void test_list_back(void);
void test_list_resize(void);
void test_list_remove(void);
void test_list_swap(void);
void test_list_merge(void);
void test_list_reverse();
void test_list_unique(void);
void test_list_operator(void);
void test_list_iterator(void);
void test_list_insert(void);

#endif
