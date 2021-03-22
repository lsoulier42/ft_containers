/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_queue.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louise <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 10:58:25 by louise            #+#    #+#             */
/*   Updated: 2021/03/02 10:58:26 by louise           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_queue.hpp"

void test_queue_constructor(void) {
	std::cout << std::endl << "Theses tests will focus on \033[31;1;4mconstructors\033[0m: " << std::endl;
	std::cout << "Default constructor: " << std::endl;
	ft::queue<int> test_constructor1;
	std::cout << "Let's push() 42, 21 and 0" << std::endl;
	test_constructor1.push(42);
	test_constructor1.push(21);
	test_constructor1.push(0);
	std::cout << "Let's see back() of the first stack : " << test_constructor1.back() << std::endl;
	std::cout << "Let's see front() of the first stack : " << test_constructor1.front() << std::endl;
	std::cout << "Let's test the copy constructor and create a new container from the first one: " << std::endl;
	ft::queue<int> test_constructor2 = ft::queue<int>(test_constructor1);
	std::cout << "Let's see back() of the second stack : " << test_constructor2.back() << std::endl;
	std::cout << "Let's see front() of the first stack : " << test_constructor2.front() << std::endl;
	std::cout << "Let's remove the back with pop()" << std::endl;
	test_constructor2.pop();
	std::cout << "Let's see back() of the second stack : " << test_constructor2.back() << std::endl;
	std::cout << "Let's see front() of the first stack : " << test_constructor2.front() << std::endl;
	std::cout << "Let's try the assignation operator from the second stack: " << std::endl;
	ft::queue<int> test_assignation;
	test_assignation = test_constructor2;
	std::cout << "Let's see back() of the third stack : " << test_assignation.back() << std::endl;
	std::cout << "Let's see front() of the first stack : " << test_assignation.front() << std::endl;
}

void test_queue_push(void) {
	std::cout << std::endl << "Theses tests will focus on \033[31;1;4mpush(), back() && front()\033[0m: " << std::endl;
	ft::queue<std::string> test_push;
	std::cout << "Let's push() 'batman', 'robin' and 'pikachu'" << std::endl;
	test_push.push("batman");
	std::cout << "Let's see back() of the stack : " << test_push.back() << std::endl;
	std::cout << "Let's see front() of the stack : " << test_push.front() << std::endl;
	test_push.push("robin");
	std::cout << "Let's see back() of the stack : " << test_push.back() << std::endl;
	std::cout << "Let's see front() of the stack : " << test_push.front() << std::endl;
	test_push.push("pikachu");
	std::cout << "Let's see back() of the stack : " << test_push.back() << std::endl;
	std::cout << "Let's see front() of the stack : " << test_push.front() << std::endl;
}

void test_queue_pop(void) {
	std::cout << std::endl << "Theses tests will focus on \033[31;1;4mpop(), back() && front()\033[0m: " << std::endl;
	ft::queue<std::string> test_pop;
	std::cout << "Let's push() 'batman', 'robin' and 'pikachu'" << std::endl;
	test_pop.push("batman");
	test_pop.push("robin");
	test_pop.push("pikachu");
	std::cout << "Let's see back() of the stack : " << test_pop.back() << std::endl;
	std::cout << "Let's see front() of the stack : " << test_pop.front() << std::endl;
	std::cout << "Now let's use pop(): " << std::endl;
	test_pop.pop();
	std::cout << "Let's see back() of the stack : " << test_pop.back() << std::endl;
	std::cout << "Let's see front() of the stack : " << test_pop.front() << std::endl;
	test_pop.pop();
	std::cout << "Let's see back() of the stack : " << test_pop.back() << std::endl;
	std::cout << "Let's see front() of the stack : " << test_pop.front() << std::endl;
	test_pop.pop();
	std::cout << "Let's see back() of the stack : " << test_pop.back() << std::endl;
	std::cout << "Let's see front() of the stack : " << test_pop.front() << std::endl;
}

void test_queue_size(void) {
	std::cout << std::endl << "Theses tests will focus on \033[31;1;4mempty() and size()\033[0m: " << std::endl;
	ft::queue<std::string> test_size;
	std::cout << "Let's see the size() on empty container: " << test_size.size();
	std::cout << " and empty() is: " << verbose_bool(test_size.empty()) << std::endl;
	std::cout << "Let's push() 'batman'" << std::endl;
	test_size.push("batman");
	std::cout << "Let's see size() of the stack : " << test_size.size();
	std::cout << " and empty() is: " << verbose_bool(test_size.empty()) << std::endl;
	std::cout << "Let's push() 'robin'" << std::endl;
	test_size.push("robin");
	std::cout << "Let's see size() of the stack : " << test_size.size();
	std::cout << " and empty() is: " << verbose_bool(test_size.empty()) << std::endl;
	std::cout << "Let's push() 'pikachu'" << std::endl;
	test_size.push("pikachu");
	std::cout << "Let's see size() of the stack : " << test_size.size();
	std::cout << " and empty() is: " << verbose_bool(test_size.empty()) << std::endl;
	std::cout << "Let's use pop(): " << std::endl;
	test_size.pop();
	std::cout << "Let's see size() of the stack : " << test_size.size();
	std::cout << " and empty() is: " << verbose_bool(test_size.empty()) << std::endl;
	std::cout << "Let's use pop(): " << std::endl;
	test_size.pop();
	std::cout << "Let's see size() of the stack : " << test_size.size();
	std::cout << " and empty() is: " << verbose_bool(test_size.empty()) << std::endl;
	std::cout << "Let's use pop(): " << std::endl;
	test_size.pop();
	std::cout << "Let's see size() of the stack : " << test_size.size();
	std::cout << " and empty() is: " << verbose_bool(test_size.empty()) << std::endl;
}

void test_queue_swap(void) {
	std::cout << std::endl << "Theses tests will focus on \033[31;1;4mswap()\033[0m: " << std::endl;
	ft::queue<double> test_swap1, test_swap2;
	std::cout << "Let's create a stack of double with 3.14, 42.21 :" << std::endl;
	test_swap1.push(3.14);
	std::cout << "The back() of the first stack is : " << test_swap1.back() << std::endl;
	std::cout << "The front() of the first stack is : " << test_swap1.front() << std::endl;
	test_swap1.push(42.21);
	std::cout << "The back() of the first stack is : " << test_swap1.back() << std::endl;
	std::cout << "The front() of the first stack is : " << test_swap1.front() << std::endl;
	std::cout << "The size() is : " << test_swap1.size() << std::endl;
	std::cout << "Let's create a second stack of double with 4.815162342 : " << std::endl;
	test_swap2.push(4.815162342);
	std::cout << "The back() of the second stack is : " << test_swap2.back() << std::endl;
	std::cout << "The front() of the second stack is : " << test_swap2.front() << std::endl;
	std::cout << "The size() is : " << test_swap2.size() << std::endl;
	std::cout << "Now let's use test_swap1.swap(test_swap2) :" << std::endl;
	test_swap1.swap(test_swap2);
	std::cout << "Let's see if it changes anything: " << std::endl;
	std::cout << "The back() of the first stack is : " << test_swap1.back() << std::endl;
	std::cout << "The front() of the first stack is : " << test_swap1.front() << std::endl;
	std::cout << "The size() is : " << test_swap1.size() << std::endl;
	std::cout << "The back() of the second stack is : " << test_swap2.back() << std::endl;
	std::cout << "The front() of the second stack is : " << test_swap2.front() << std::endl;
	std::cout << "The size() is : " << test_swap2.size() << std::endl;
}

void test_queue_comparison(void) {
	std::cout << std::endl << "Theses tests will focus on \033[31;1;4mcomparison operators\033[0m: " << std::endl;
	ft::queue<char> test_comparison1, test_comparison2;
	std::cout << "Let's create two identical char stacks with 'a', 'b', 'c', 'd' : " << std::endl;
	test_comparison1.push('a');
	test_comparison2.push('a');
	test_comparison1.push('b');
	test_comparison2.push('b');
	test_comparison1.push('c');
	test_comparison2.push('c');
	test_comparison1.push('d');
	test_comparison2.push('d');
	std::cout << "back() of the first stack is: " << test_comparison1.back() << std::endl;
	std::cout << "front() of the first stack is: " << test_comparison1.front() << std::endl;
	std::cout << " and size() is : " << test_comparison1.size() << std::endl;
	std::cout << "back() of the second stack is: " << test_comparison2.back() << std::endl;
	std::cout << "front() of the first stack is: " << test_comparison2.front() << std::endl;
	std::cout << " and size() is : " << test_comparison2.size() << std::endl;
	std::cout << "The return of test_comparison1 == test_comparaison2 is : ";
	std::cout << verbose_bool(test_comparison1 == test_comparison2) << std::endl;
	std::cout << "The return of test_comparison1 != test_comparaison2 is : ";
	std::cout << verbose_bool(test_comparison1 != test_comparison2) << std::endl;
	std::cout << "The return of test_comparison1 < test_comparaison2 is : ";
	std::cout << verbose_bool(test_comparison1 < test_comparison2) << std::endl;
	std::cout << "The return of test_comparison1 <= test_comparaison2 is : ";
	std::cout << verbose_bool(test_comparison1 <= test_comparison2) << std::endl;
	std::cout << "The return of test_comparison1 > test_comparaison2 is : ";
	std::cout << verbose_bool(test_comparison1 > test_comparison2) << std::endl;
	std::cout << "The return of test_comparison1 >= test_comparaison2 is : ";
	std::cout << verbose_bool(test_comparison1 >= test_comparison2) << std::endl;

	std::cout << std::endl << "Let's create one char stacks with 'a', 'b', 'c', 'd', ";
	std::cout << "and a second stack with 'e', 'f', 'g', 'h'" << std::endl;
	test_comparison2.pop();
	test_comparison2.pop();
	test_comparison2.pop();
	test_comparison2.pop();
	test_comparison2.push('e');
	test_comparison2.push('f');
	test_comparison2.push('g');
	test_comparison2.push('h');
	std::cout << "back() of the first stack is: " << test_comparison1.back() << std::endl;
	std::cout << "front() of the first stack is: " << test_comparison1.front() << std::endl;
	std::cout << " and size() is : " << test_comparison1.size() << std::endl;
	std::cout << "back() of the second stack is: " << test_comparison2.back() << std::endl;
	std::cout << "front() of the first stack is: " << test_comparison2.front() << std::endl;
	std::cout << " and size() is : " << test_comparison2.size() << std::endl;
	std::cout << "The return of test_comparison1 == test_comparaison2 is : ";
	std::cout << verbose_bool(test_comparison1 == test_comparison2) << std::endl;
	std::cout << "The return of test_comparison1 != test_comparaison2 is : ";
	std::cout << verbose_bool(test_comparison1 != test_comparison2) << std::endl;
	std::cout << "The return of test_comparison1 < test_comparaison2 is : ";
	std::cout << verbose_bool(test_comparison1 < test_comparison2) << std::endl;
	std::cout << "The return of test_comparison1 <= test_comparaison2 is : ";
	std::cout << verbose_bool(test_comparison1 <= test_comparison2) << std::endl;
	std::cout << "The return of test_comparison1 > test_comparaison2 is : ";
	std::cout << verbose_bool(test_comparison1 > test_comparison2) << std::endl;
	std::cout << "The return of test_comparison1 >= test_comparaison2 is : ";
	std::cout << verbose_bool(test_comparison1 >= test_comparison2) << std::endl;
}

void test_queue(void) {
	std::cout << "Theses tests will focus on container \033[31;1;4mqueue\033[0m:" << std::endl;
	test_queue_constructor();
	test_queue_push();
	test_queue_pop();
	test_queue_size();
	test_queue_swap();
	test_queue_comparison();
}