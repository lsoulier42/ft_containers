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
#include <limits>
#define ARRAY_SIZE 5

const char* verbose_bool(bool b) {
	return b ? "true" : "false";
}

void print_list(ft::list<int> & current_list) {
	std::cout << "Let's print list using size() in for() : ";
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
	test_list_int_exceptions();
}

void test_list(void) {
	std::cout << "Tests with \033[31;1;4mft::list<>\033[0m container: " << std::endl;
	test_list_int();
}

int main() {
	std::srand(time(NULL));
	test_list();
}
