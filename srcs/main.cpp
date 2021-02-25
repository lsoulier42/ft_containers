/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 13:15:20 by lsoulier          #+#    #+#             */
/*   Updated: 2021/02/19 13:15:47 by lsoulier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "list.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>
#define ARRAY_SIZE 5
#ifdef __linux__
# include <climits>
#endif
#ifdef __apple__
# include <limits>
#endif

const char* verbose_bool(bool b) {
	return b ? "true" : "false";
}

void print_list(ft::list<int> & current_list) {
	std::cout << "This list contains the following ints : ";
	for (size_t i = 0; i < current_list.size(); i++)
		std::cout << current_list[i] << ", ";
	std::cout << std::endl;
}

void create_int_container(ft::list<int> *container_ptr) {
	int ints[ARRAY_SIZE] = { std::rand(), 42, -42, INT_MAX, INT_MIN };
	std::cout << "Ints that will be pushed: ";
	for (int i = 0; i < ARRAY_SIZE; i++)
		std::cout << ints[i] << ", ";
	std::cout << std::endl;
	for (int i = 0; i < ARRAY_SIZE; i++)
		container_ptr->push_back(ints[i]);
}

void test_list_int_push_back(void) {
	ft::list<int> test_push_back;

	std::cout << std::endl << "Function \033[31;4mpush_back()\033[0m :" << std::endl;
	create_int_container(&test_push_back);
	print_list(test_push_back);
}

void test_list_int_size(void) {
	ft::list<int> test_size;

	std::cout << std::endl << "Function \033[31;4msize()\033[0m : " << std::endl;
	create_int_container(&test_size);
	std::cout << "Size of the containter: " << test_size.size() << std::endl;
}

void test_list_int_pop_back(void) {
	ft::list<int> test_pop_back;

	std::cout << std::endl << "Function \033[31;4mpop_back()\033[0m : " << std::endl;
	create_int_container(&test_pop_back);
	std::cout << "Let's remove 2 elements: " << std::endl;
	test_pop_back.pop_back();
	test_pop_back.pop_back();
	print_list(test_pop_back);
}

void test_list_int_clear(void) {
	ft::list<int> test_clear;

	std::cout << std::endl << "Function \033[31;4mclear()\033[0m : " << std::endl;
	create_int_container(&test_clear);
	std::cout << "The current size is: " << test_clear.size() << std::endl;
	std::cout << "Return of empty() function: " << verbose_bool(test_clear.empty()) << std::endl;
	std::cout << "Let's remove everything: " << std::endl;
	test_clear.clear();
	std::cout << "The new size is: " << test_clear.size() << std::endl;
	std::cout << "Return of empty() function: " << verbose_bool(test_clear.empty()) << std::endl;
}

void test_list_int_push_front(void) {
	ft::list<int> test_push_front;
	int add[2] = {15, 89};

	std::cout << std::endl << "Function \033[31;4mpush_front()\033[0m: " << std::endl;
	create_int_container(&test_push_front);
	std::cout << "Let's add 2 more ints at the begining of the list: ";
	std::cout << add[0] << ", " << add[1] << std::endl;
	test_push_front.push_front(add[0]);
	test_push_front.push_front(add[1]);
	print_list(test_push_front);
}

void test_list_int_pop_front(void) {
	ft::list<int> test_pop_front;

	std::cout << std::endl << "Function \033[31;4mpop_front()\033[0m: " << std::endl;
	create_int_container(&test_pop_front);
	std::cout << "Let's remove the 2 firsts elements " << std::endl;
	test_pop_front.pop_front();
	test_pop_front.pop_front();
	print_list(test_pop_front);
}

void test_list_int_exceptions(void) {
	ft::list<int> test_exceptions;

	std::cout << std::endl << "\033[31;4mException tests\033[0m: " << std::endl;
	create_int_container(&test_exceptions);
	try {
		int element = std::rand();
		std::cout << "Will try to access element: " << element << " -> ";
		int exceptionInt = test_exceptions[element];
		std::cout << exceptionInt << "(wrong should not have happened)" << std::endl;
	}
	catch (std::exception & e) {
		std::cout << e.what() << std::endl;
	}
}

void test_list_int_assign(void) {
	ft::list<int> test_assign;

	std::cout << std::endl << "Function \033[31;4massign()\033[0m: " << std::endl;
	create_int_container(&test_assign);
	std::cout << "Let's use assign with 11 as count and 21 as value." << std::endl;
	test_assign.assign(11, 21);
	print_list(test_assign);
}

void test_list_int_front(void) {
	ft::list<int> test_front;

	std::cout << std::endl << "Function \033[31;4mfront()\033[0m: " << std::endl;
	create_int_container(&test_front);
	std::cout << "The return of front function is : " << test_front.front() << std::endl;
}

void test_list_int_back(void) {
	ft::list<int> test_back;

	std::cout << std::endl << "Function \033[31;4mback()\033[0m: " << std::endl;
	create_int_container(&test_back);
	std::cout << "The return of back function is : " << test_back.back() << std::endl;
}

void test_list_int_resize(void) {
	ft::list<int> test_resize;

	std::cout << std::endl << "Function \033[31;4mresize()\033[0m: " << std::endl;
	create_int_container(&test_resize);
	std::cout << "Let's resize with a count(4) < size() :" << std::endl;
	test_resize.resize(4);
	print_list(test_resize);
	std::cout << "Let's resize with a count(8) > size() and a value of 21 :" << std::endl;
	test_resize.resize(8, 21);
	print_list(test_resize);
}

void test_list_int_remove(void) {
	ft::list<int> test_remove;

	std::cout << std::endl << "Function \033[31;4mremove()\033[0m: " << std::endl;
	create_int_container(&test_remove);
	std::cout << "Let's remove the element 42 :" << std::endl;
	test_remove.remove(42);
	print_list(test_remove);
	std::cout << "Let's remove the last element:" << std::endl;
	test_remove.remove(INT_MIN);
	print_list(test_remove);
	std::cout << "The last element using back(): " << test_remove.back() << std::endl;

	ft::list<int> test_one_el;
	int rand_nb = std::rand();
	test_one_el.push_back(rand_nb);
	std::cout << "Let's test with a list with a unique int" << std::endl;
	print_list(test_one_el);
	std::cout << "Let's remove the element and test size() and empty(): " << std::endl;
	test_one_el.remove(rand_nb);
	std::cout << "Size(): " << test_one_el.size() << std::endl;
	std::cout << "Empty(): " << verbose_bool(test_one_el.empty()) << std::endl;
}

void test_list_int_swap(void) {
	ft::list<int> test_swap;
	ft::list<int> test_swap2;

	std::cout << std::endl << "Function \033[31;4mswap()\033[0m: " << std::endl;
	create_int_container(&test_swap);
	std::cout << "Let's create a second list with 45, 55, 65" << std::endl;
	test_swap2.push_back(45);
	test_swap2.push_back(55);
	test_swap2.push_back(65);
	std::cout << "First list : " << std::endl;
	print_list(test_swap);
	std::cout << "Second list : " << std::endl;
	print_list(test_swap2);
	std::cout << "Let's use swap() :" << std::endl;
	test_swap.swap(test_swap2);
	std::cout << "First list : " << std::endl;
	print_list(test_swap);
	std::cout << "Second list : " << std::endl;
	print_list(test_swap2);
}

void test_list_int_merge(void) {
	ft::list<int> merge1, merge2;
	ft::list<int> merge3, merge4;
	ft::list<int> merge5, merge6;

	std::cout << std::endl << "Function \033[31;4mmerge()\033[0m: " << std::endl;
	std::cout << "List 2 won't affect list 1 _begin and _end :" << std::endl;
	merge1.push_back(1);
	merge1.push_back(3);
	merge1.push_back(5);
	merge1.push_back(7);
	merge1.push_back(9);
	print_list(merge1);
	merge2.push_back(2);
	merge2.push_back(4);
	merge2.push_back(6);
	merge2.push_back(8);
	print_list(merge2);
	merge1.merge(merge2);
	std::cout << "Now list 1 is :" << std::endl;
	print_list(merge1);
	std::cout << "Let's see if list 2 is clear :" << std::endl;
	print_list(merge2);

	std::cout << "List 2 affects list 1 _begin:" << std::endl;
	merge3.push_back(1);
	merge3.push_back(3);
	merge3.push_back(5);
	merge3.push_back(7);
	merge3.push_back(9);
	print_list(merge3);
	merge4.push_back(0);
	merge4.push_back(2);
	print_list(merge4);
	merge3.merge(merge4);
	std::cout << "Now list 1 is :" << std::endl;
	print_list(merge3);
	std::cout << "The return of front() is : " << merge3.front() << std::endl;

	std::cout << "List 2 affects list 1 _end:" << std::endl;
	merge5.push_back(1);
	merge5.push_back(3);
	merge5.push_back(5);
	merge5.push_back(7);
	merge5.push_back(9);
	print_list(merge5);
	merge6.push_back(2);
	merge6.push_back(10);
	print_list(merge6);
	merge5.merge(merge6);
	std::cout << "Now list 1 is :" << std::endl;
	print_list(merge5);
	std::cout << "The return of back() is : " << merge5.back() << std::endl;
}

void test_list_int_reverse() {
	ft::list<int> reverse_test;

	std::cout << std::endl << "Function \033[31;4mreverse()\033[0m: " << std::endl;
	create_int_container(&reverse_test);
	print_list(reverse_test);
	std::cout << "Let's use reverse() on this list." << std::endl;
	reverse_test.reverse();
	print_list(reverse_test);
	std::cout << "The return of front() is now: " << reverse_test.front() << std::endl;
	std::cout << "The return of back() is now: " << reverse_test.back() << std::endl;
}

void test_list_int_unique(void) {
	ft::list<int> unique_test;

	std::cout << std::endl << "Function \033[31;4munique()\033[0m: " << std::endl;
	unique_test.push_back(1);
	unique_test.push_back(1);
	unique_test.push_back(2);
	unique_test.push_back(2);
	unique_test.push_back(3);
	unique_test.push_back(3);
	unique_test.push_back(3);
	unique_test.push_back(2);
	unique_test.push_back(1);
	unique_test.push_back(1);
	unique_test.push_back(2);
	unique_test.push_back(2);
	print_list(unique_test);
	std::cout << "The size is: " << unique_test.size() << std::endl;
	std::cout << "Let's use the unique() function." << std::endl;
	unique_test.unique();
	print_list(unique_test);
	std::cout << "The return of back() is: " << unique_test.back() << std::endl;
	std::cout << "The size is now: " << unique_test.size() << std::endl;
}

/*void test_list_int_sort(void) {
	ft::list<int> sort_test;

	std::cout << std::endl << "Function \033[31;4msort()\033[0m: " << std::endl;
	sort_test.push_back(8);
	sort_test.push_back(7);
	sort_test.push_back(5);
	sort_test.push_back(9);
	sort_test.push_back(0);
	sort_test.push_back(1);
	sort_test.push_back(3);
	sort_test.push_back(2);
	sort_test.push_back(6);
	sort_test.push_back(4);
	print_list(sort_test);
	std::cout << "Let's use sort() fct:" << std::endl;
	sort_test.sort();
	print_list(sort_test);
}*/

void test_list_int(void) {
	std::cout << "\033[31;1;4mInt container\033[0m: ";
	test_list_int_push_back();
	test_list_int_size();
	test_list_int_pop_back();
	test_list_int_clear();
	test_list_int_push_front();
	test_list_int_pop_front();
	test_list_int_assign();
	test_list_int_front();
	test_list_int_back();
	test_list_int_resize();
	test_list_int_remove();
	test_list_int_swap();
	test_list_int_merge();
	test_list_int_reverse();
	test_list_int_unique();
	//test_list_int_sort();
	test_list_int_exceptions();
}

void test_list(void) {
	std::cout << "Tests with \033[31;1;4mft::list<>\033[0m container: " << std::endl;
	test_list_int();
}
#include <list>
int main() {
	std::srand(time(NULL));
	test_list();
}
