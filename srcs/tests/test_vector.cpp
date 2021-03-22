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
void print_vector_content(const ft::vector<T>& to_print) {
	std::cout << "The vector contains : ";
	for(size_t i = 0; i < to_print.size(); i++)
		std::cout << to_print[i] << ", ";
	std::cout << std::endl;
}

template<typename T>
void print_vector_state(const ft::vector<T>& to_print) {
	print_vector_content(to_print);
	std::cout << "The size() is: " << to_print.size();
	std::cout << ", so empty() is " << verbose_bool(to_print.empty());
	std::cout << ", and capacity() is " << to_print.capacity() << std::endl;
}

void test_vector_constructor(void) {
	std::cout << std::endl << "Tests for \033[31;1;4mconstructors\033[0m: " << std::endl;
	std::cout << "Let's use the default constructor";
	std::cout << " and print the state of the first vector: " << std::endl;
	ft::vector<std::string> test_constructor1;
	print_vector_state(test_constructor1);

	std::cout << std::endl << "Now let's push 'salameche' and 'pikachu'";
	std::cout << " and print the state of the first vector: ";
	test_constructor1.push_back("salameche");
	test_constructor1.push_back("pikachu");
	print_vector_state(test_constructor1);

	std::cout << std::endl << "Let's use the copy constructor and print the state the second vector: " << std::endl;
	ft::vector<std::string> test_constructor2 = ft::vector<std::string>(test_constructor1);
	print_vector_state(test_constructor2);

	std::cout << std::endl << "Let's use the constructor with 42 copies of default T(): " << std::endl;
	ft::vector<std::string> test_constructor3 = ft::vector<std::string>(42);
	print_vector_state(test_constructor3);

	std::cout << std::endl << "Let's use the constructor with 42 copies of 'melofee': " << std::endl;
	ft::vector<std::string> test_constructor4 = ft::vector<std::string>(42, "melofee");
	print_vector_state(test_constructor4);

	std::cout << std::endl << "Let's use the constructor with InputIt from the first vector: " << std::endl;
	ft::vector<std::string> test_constructor5 = ft::vector<std::string>(test_constructor1.begin(), test_constructor1.end());
	print_vector_state(test_constructor5);

	std::cout << std::endl << "Finaly let's try the assignation with the melofee vector " << std::endl;
	ft::vector<std::string> test_constructor6;
	test_constructor6 = test_constructor4;
	print_vector_state(test_constructor6);
}

void test_vector_pushpop_back(void) {
	std::cout << std::endl << "Tests for \033[31;1;4mpush_back()\033[0m: " << std::endl;
	ft::vector<std::string> test_push_back;

	std::cout << "Let's create a vector then push_back() 'mewtwo', 'articodin' and 'raflesia': " << std::endl;
	test_push_back.push_back("mewtwo");
	print_vector_state(test_push_back);
	test_push_back.push_back("articodin");
	print_vector_state(test_push_back);
	test_push_back.push_back("raflesia");
	print_vector_state(test_push_back);

	std::cout << "Now let's use pop_back() three times: " << std::endl;
	test_push_back.pop_back();
	print_vector_state(test_push_back);
	test_push_back.pop_back();
	print_vector_state(test_push_back);
	test_push_back.pop_back();
	print_vector_state(test_push_back);
}

void test_vector_assign(void) {
	std::cout << std::endl << "Tests for \033[31;1;4massign()\033[0m: " << std::endl;
	ft::vector<std::string> test_assign1;

	std::cout << "Let's try assign 21 'roudoudou' on an empty vector: " << std::endl;
	test_assign1.assign(21, "roudoudou");
	print_vector_state(test_assign1);

	ft::vector<std::string> test_assign2;
	std::cout << std::endl << "Let's create a second vector then push_back() 'mewtwo', 'articodin' and 'raflesia': "
			  << std::endl;
	test_assign2.push_back("mewtwo");
	test_assign2.push_back("articodin");
	test_assign2.push_back("raflesia");
	print_vector_state(test_assign2);
	std::cout << "Let's try assign 12 'asticot' on this non empty vector: " << std::endl;
	test_assign2.assign(12, "asticot");
	print_vector_state(test_assign2);

	ft::vector<std::string> test_assign3;
	std::cout << std::endl << "Let's create an third empty container";
	std::cout << ", and use assign with iterators from the first container:" << std::endl;
	test_assign3.assign(test_assign1.begin(), test_assign1.end());
	print_vector_state(test_assign3);
}

void test_vector_frontback(void) {
	std::cout << std::endl << "Tests for \033[31;1;4mfront() & back()\033[0m: " << std::endl;
	ft::vector<std::string> test_front;

	std::cout << "What contains front() and back() on an empty container ?" << std::endl;
	std::cout << "front() :" << test_front.front() << std::endl;
	std::cout << "back() :" << test_front.back() << std::endl;
	std::cout << "Let's create a vector with 'raichu', 'machopeur' and 'nosferapti': " << std::endl;
	test_front.push_back("raichu");
	std::cout << "front() :" << test_front.front() << std::endl;
	std::cout << "back() :" << test_front.back() << std::endl;
	test_front.push_back("machopeur");
	std::cout << "front() :" << test_front.front() << std::endl;
	std::cout << "back() :" << test_front.back() << std::endl;
	test_front.push_back("nosferapti");
	std::cout << "front() :" << test_front.front() << std::endl;
	std::cout << "back() :" << test_front.back() << std::endl;
	std::cout << "Let's pop_back twice: " << std::endl;
	test_front.pop_back();
	std::cout << "front() :" << test_front.front() << std::endl;
	std::cout << "back() :" << test_front.back() << std::endl;\
	test_front.pop_back();
	std::cout << "front() :" << test_front.front() << std::endl;
	std::cout << "back() :" << test_front.back() << std::endl;
}

void test_vector_insert(void) {
	std::cout << std::endl << "Tests for \033[31;1;4minsert()\033[0m: " << std::endl;

	std::cout << "Let's insert on empty vector<int> container:" << std::endl;
	ft::vector<int> test_insert1;
	std::cout << "*First let's try to insert at pos = begin() with integer 42 :" << std::endl;
	test_insert1.insert(test_insert1.begin(), 42);
	print_vector_state(test_insert1);
	std::cout << "*Let's create a new empty container and try to insert at pos = end() with integer 42 :" << std::endl;
	ft::vector<int> test_insert2;
	test_insert2.insert(test_insert2.end(), 42);
	print_vector_state(test_insert2);

	std::cout << std::endl << "Let's insert on vector<int> container with one element 42 (the previous one):" << std::endl;
	std::cout << "*First let's try to insert at pos = begin() with integer 21 :" << std::endl;
	test_insert1.insert(test_insert1.begin(), 21);
	print_vector_state(test_insert1);
	std::cout << "*Then let's try to insert at pos = end() with integer 12 :" << std::endl;
	test_insert1.insert(test_insert1.end(), 12);
	print_vector_state(test_insert1);
	std::cout << "Let's try to insert with pos = begin() + 2 with integer 123: " << std::endl;
	test_insert1.insert(test_insert1.begin() + 2, 123);
	print_vector_state(test_insert1);
	std::cout << "*Then let's try to insert at pos = end() - 2 with integer 789 :" << std::endl;
	test_insert1.insert(test_insert1.end() - 2, 789);
	print_vector_state(test_insert1);

	std::cout << std::endl << "Let's use the insert(pos, count, val) prototype with pos = begin() + 1, ";
	std::cout << "count = 9 and val = '666' on the previous container" << std::endl;
	test_insert1.insert(test_insert1.begin() + 1, 9, 666);
	print_vector_state(test_insert1);
	std::cout << "The use the insert(pos, count, val) prototype with pos = end(), ";
	std::cout << "count = 5 and val = '75' on the previous container" << std::endl;
	test_insert1.insert(test_insert1.end(), 5, 75);
	print_vector_state(test_insert1);

	std::cout << std::endl << "Let's use the insert prototype with input iterators :" << std::endl;
	std::cout << "Let's create a new vector<int> with 12 integer -1:" << std::endl;
	ft::vector<int> test_insert3 = ft::vector<int>(12, -1);
	print_vector_state(test_insert3);
	std::cout << "Then let's try to insert this new vector at the end of the previous one:" << std::endl;
	test_insert1.insert(test_insert1.end(), test_insert3.begin(), test_insert3.end());
	print_vector_state(test_insert1);
}

void test_vector_erase(void) {
	std::cout << std::endl << "Tests for \033[31;1;4merase()\033[0m: " << std::endl;

	std::cout << "Let's create an empty container:" << std::endl;
	ft::vector<std::string> test_erase1;
	print_vector_state(test_erase1);

	std::cout << "Let's try to erase begin() on empty container:" << std::endl;
	test_erase1.erase(test_erase1.begin());
	print_vector_state(test_erase1);

	std::cout << "Let's create a vector<string> with 'carapuce', 'carabaffe' and 'tortank':" << std::endl;
	test_erase1.push_back("carapuce");
	test_erase1.push_back("carabaffe");
	test_erase1.push_back("tortank");
	print_vector_state(test_erase1);
	std::cout << "Let's try to erase begin():" << std::endl;
	test_erase1.erase(test_erase1.begin());
	print_vector_state(test_erase1);
	std::cout << "Let's try to erase begin() + 1:" << std::endl;
	test_erase1.erase(test_erase1.begin() + 1);
	print_vector_state(test_erase1);
}

void test_vector_at(void) {

}

void test_vector_operator_crochet(void) {

}

void test_vector_clear(void) {

}

void test_vector_max_size(void) {

}

void test_vector_reserve(void) {

}

void test_vector_resize(void) {

}

void test_vector_iterator(void) {

}

void test_vector_comparison(void) {

}

void test_vector_swap(void) {

}

void test_vector() {
	std::cout << "Tests for \033[31;1;4mvector()\033[0m container: " << std::endl;
	test_vector_constructor();
	test_vector_pushpop_back();
	test_vector_assign();
	test_vector_frontback();
	test_vector_insert();
	test_vector_erase();

}