/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_vector.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <lsoulier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 14:48:40 by lsoulier          #+#    #+#             */
/*   Updated: 2021/03/07 14:48:49 by lsoulier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_vector.hpp"

template<typename T>
void print_vector_content(const ft::Vector<T>& to_print) {
	std::cout << "The vector contains : ";
	for(size_t i = 0; i < to_print.size(); i++)
		std::cout << to_print[i] << ", ";
	std::cout << std::endl;
}

template<typename T>
void print_vector_state(const ft::Vector<T>& to_print) {
	std::cout << "The size() is: " << to_print.size();
	std::cout << ", so empty() is " << verbose_bool(to_print.empty());
	std::cout << ", and capacity() is " << to_print.capacity() << std::endl;
}

void test_vector() {
	std::cout << "Tests for \033[31;1;4mVector()\033[0m container: " << std::endl;
	ft::Vector<std::string> test_insert;
	print_vector_content(test_insert);
	print_vector_state(test_insert);
	std::cout << std::endl;

	std::cout << "Test for \033[31;1;4mpush_back()\033[0m function:" << std::endl;
	std::string phrase1 = "batman";
	std::string phrase2 = "robin";
	std::string phrase3 = "superman";
	std::string phrase4 = "spiderman";
	std::cout << "Let's push this sentences : ";
	std::cout << phrase1 << ", " << phrase2 << ", " << phrase3 << ", " << phrase4 << std::endl;
	test_insert.push_back(phrase1);
	test_insert.push_back(phrase2);
	test_insert.push_back(phrase3);
	test_insert.push_back(phrase4);
	print_vector_content(test_insert);
	print_vector_state(test_insert);

	std::cout << std::endl;
	std::cout << "Test for \033[31;1;4mpop_back()\033[0m function: it's going to be used twice" << std::endl;
	test_insert.pop_back();
	test_insert.pop_back();
	print_vector_content(test_insert);
	print_vector_state(test_insert);

	std::cout << std::endl;
	std::cout << "Test for \033[31;1;4mfront()\033[0m function: ";
	std::cout << test_insert.front() << std::endl;

	std::cout << std::endl;
	std::cout << "Test for \033[31;1;4mback()\033[0m function: ";
	std::cout << test_insert.back() << std::endl;

	std::cout << std::endl << "Let's create a new container using count = 7";
	std::cout << " in \033[31;1;4mconstructor\033[0m and 'pika' as default alue" << std::endl;
	ft::Vector<std::string> test_constructor(7, "pika");
	print_vector_content(test_constructor);
	print_vector_state(test_constructor);

	std::cout << std::endl << "Let's try to \033[31;1;4massign()\033[0m with 9 elements 'melofee'" << std::endl;
	test_constructor.assign(9, "melofee");
	print_vector_content(test_constructor);
	print_vector_state(test_constructor);

	std::cout << std::endl << "Now let's test \033[31;1;4m*begin()\033[0m: " << *test_constructor.begin() << std::endl;
	std::cout << std::endl << "Let's test \033[31;1;4minsert()\033[0m at begin()" << std::endl;
	test_constructor.insert(test_constructor.begin(), "pikachu");
	print_vector_content(test_constructor);
	print_vector_state(test_constructor);
	std::cout << std::endl << "Let's test \033[31;1;4minsert()\033[0m at begin() + 3" << std::endl;
	test_constructor.insert(test_constructor.begin() + 3, "ratata");
	print_vector_content(test_constructor);
	print_vector_state(test_constructor);

}