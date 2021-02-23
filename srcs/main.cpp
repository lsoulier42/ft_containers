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
#define ARRAY_SIZE 5

void test_list_int(void) {
	std::cout << "Int container: " << std::endl;
	ft::list<int> first_test;

	//push back test
	std::cout << "Function push_back(): " << std::endl;
	int ints[ARRAY_SIZE] = { 5, 123, 0, -15, 789456123 };
	std::cout << "Ints that will be pushed: ";
	for (int i = 0; i < ARRAY_SIZE; i++)
		std::cout << ints[i] << ", ";
	std::cout << std::endl;
	for (int i = 0; i < ARRAY_SIZE; i++)
		first_test.push_back(ints[i]);
	std::cout << "Lets try to access it with operator[]: ";
	for (int i = 0; i < ARRAY_SIZE; i++)
		std::cout << first_test[i] << ", ";
	std::cout << std::endl;

	std::cout << "Exception test: " << std::endl;
	try {
		int exceptionInt = first_test[6000];
		std::cout << "Shouldn't happen : " << exceptionInt << std::endl;
	}
	catch (std::exception & e) {
		std::cout << e.what() << std::endl;
	}
}

void test_list(void) {
	std::cout << "Tests with list container: " << std::endl;
	test_list_int();
}

int main() {
	test_list();
}
