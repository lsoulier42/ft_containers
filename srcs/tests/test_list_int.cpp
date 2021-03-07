/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_list_int.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoulier <lsoulier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 11:01:43 by lsoulier          #+#    #+#             */
/*   Updated: 2021/03/01 11:01:48 by lsoulier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_list.hpp"

void print_list(ft::List<int> & current_list) {
	std::cout << "This list contains the following ints : ";
	if (!current_list.empty())
		for (ft::List<int>::iterator fit = current_list.begin(); fit != current_list.end(); fit++)
			std::cout << *fit << ", ";
	std::cout << std::endl;
}

void create_int_container(ft::List<int> *container_ptr) {
	int ints[ARRAY_SIZE] = { std::rand(), 42, -42, INT_MAX, INT_MIN };
	std::cout << "Ints that will be pushed: ";
	for (int i = 0; i < ARRAY_SIZE; i++)
		std::cout << ints[i] << ", ";
	std::cout << std::endl;
	for (int i = 0; i < ARRAY_SIZE; i++)
		container_ptr->push_back(ints[i]);
}

void test_list_int_push_back(void) {
	ft::List<int> test_push_back;

	std::cout << std::endl << "Function \033[31;4mpush_back()\033[0m :" << std::endl;
	create_int_container(&test_push_back);
	print_list(test_push_back);
}

void test_list_int_size(void) {
	ft::List<int> test_size;

	std::cout << std::endl << "Function \033[31;4msize()\033[0m : " << std::endl;
	create_int_container(&test_size);
	std::cout << "Size of the containter: " << test_size.size() << std::endl;
}

void test_list_int_pop_back(void) {
	ft::List<int> test_pop_back;

	std::cout << std::endl << "Function \033[31;4mpop_back()\033[0m : " << std::endl;
	create_int_container(&test_pop_back);
	std::cout << "Let's remove 2 elements: " << std::endl;
	test_pop_back.pop_back();
	test_pop_back.pop_back();
	print_list(test_pop_back);
}

void test_list_int_clear(void) {
	ft::List<int> test_clear;

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
	ft::List<int> test_push_front;
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
	ft::List<int> test_pop_front;

	std::cout << std::endl << "Function \033[31;4mpop_front()\033[0m: " << std::endl;
	create_int_container(&test_pop_front);
	std::cout << "Let's remove the 2 firsts elements " << std::endl;
	test_pop_front.pop_front();
	test_pop_front.pop_front();
	print_list(test_pop_front);
}

void test_list_int_assign(void) {
	ft::List<int> test_assign;

	std::cout << std::endl << "Function \033[31;4massign()\033[0m: " << std::endl;
	create_int_container(&test_assign);
	std::cout << "Let's use assign with 11 as count and 21 as value." << std::endl;
	test_assign.assign(11, 21);
	print_list(test_assign);
}

void test_list_int_front(void) {
	ft::List<int> test_front;

	std::cout << std::endl << "Function \033[31;4mfront()\033[0m: " << std::endl;
	create_int_container(&test_front);
	std::cout << "The return of front function is : " << test_front.front() << std::endl;
}

void test_list_int_back(void) {
	ft::List<int> test_back;

	std::cout << std::endl << "Function \033[31;4mback()\033[0m: " << std::endl;
	create_int_container(&test_back);
	std::cout << "The return of back function is : " << test_back.back() << std::endl;
}

void test_list_int_resize(void) {
	ft::List<int> test_resize;

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
	ft::List<int> test_remove;

	std::cout << std::endl << "Function \033[31;4mremove()\033[0m: " << std::endl;
	create_int_container(&test_remove);
	std::cout << "Let's remove the element 42 :" << std::endl;
	test_remove.remove(42);
	print_list(test_remove);
	std::cout << "Let's remove the last element:" << std::endl;
	test_remove.remove(INT_MIN);
	print_list(test_remove);
	std::cout << "The last element using back(): " << test_remove.back() << std::endl;

	ft::List<int> test_one_el;
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
	ft::List<int> test_swap;
	ft::List<int> test_swap2;

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
	ft::List<int> merge1, merge2;
	ft::List<int> merge3, merge4;
	ft::List<int> merge5, merge6;

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
	ft::List<int> reverse_test;

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
	ft::List<int> unique_test;

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

void test_list_int_sort(void) {
	ft::List<int> sort_test;

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
}

void test_list_int_operator(void) {
	ft::List<int> operator1, operator2;
	ft::List<int> operator3, operator4;

	std::cout << std::endl << "Non member overload \033[31;4moperators\033[0m: " << std::endl;
	std::cout << "Case same lists:" << std::endl;
	operator1.push_back(1);
	operator1.push_back(2);
	operator1.push_back(3);
	operator1.push_back(5);
	operator2.push_back(1);
	operator2.push_back(2);
	operator2.push_back(3);
	operator2.push_back(5);
	print_list(operator1);
	print_list(operator2);
	std::cout << "Return of operator==: " << verbose_bool(operator1 == operator2) << std::endl;
	std::cout << "Return of operator!=: " << verbose_bool(operator1 != operator2) << std::endl;
	std::cout << "Return of operator<: " << verbose_bool(operator1 < operator2) << std::endl;
	std::cout << "Return of operator<=: " << verbose_bool(operator1 <= operator2) << std::endl;
	std::cout << "Return of operator>: " << verbose_bool(operator1 > operator2) << std::endl;
	std::cout << "Return of operator>=: " << verbose_bool(operator1 >= operator2) << std::endl;

	std::cout << "Case differents lists / same size:" << std::endl;
	operator3.push_back(1);
	operator3.push_back(2);
	operator3.push_back(3);
	operator3.push_back(5);
	operator4.push_back(8);
	operator4.push_back(9);
	operator4.push_back(3);
	operator4.push_back(0);
	print_list(operator3);
	print_list(operator4);
	std::cout << "Return of operator==: " << verbose_bool(operator3 == operator4) << std::endl;
	std::cout << "Return of operator!=: " << verbose_bool(operator3 != operator4) << std::endl;
	std::cout << "Return of operator<: " << verbose_bool(operator3 < operator4) << std::endl;
	std::cout << "Return of operator<=: " << verbose_bool(operator3 <= operator4) << std::endl;
	std::cout << "Return of operator>: " << verbose_bool(operator3 > operator4) << std::endl;
	std::cout << "Return of operator>=: " << verbose_bool(operator3 >= operator4) << std::endl;
}

void test_list_int_iterator(void) {
	ft::List<int> iterator_test;
	ft::List<int>::iterator it;
	ft::List<int>::iterator ite;

	std::cout << std::endl << "Test of \033[31;4mITERATORS\033[0m: " << std::endl;
	create_int_container(&iterator_test);
	print_list(iterator_test);

	std::cout << "Let's test begin() iterator: " << std::endl;
	it = iterator_test.begin();
	std::cout << "The return of *it, with it =  list.begin() is : " << *it << std::endl;
	std::cout << "The return of *(--it) is : " << *(--it) << std::endl;
	std::cout << "The return of *(++it) is : " << *(++it) << std::endl;
	std::cout << "The return of *(it++), is : " << *(it++) << " then *it is " << *it << std::endl;
	std::cout << "The return of *(--it) is : " << *(--it) << std::endl;
	std::cout << "The return of *(it--), is : " << *(it--) << " then *it is " << *it << std::endl;

	std::cout << "Let's test end() iterator: " << std::endl;
	ite = iterator_test.end();
	std::cout << "The return of *ite, with ite = list.end() is: " << *ite << std::endl;
	std::cout << "The return of *(++ite) is :" << *(++ite) << std::endl;
	std::cout << "The return of *(ite++) is :" << *(ite++) << " then *ite is " << *ite << std::endl;
	std::cout << "The return of *(--ite) is : " << *(--ite) << std::endl;
	std::cout << "The return of *(ite--) is : " << *(ite--) << " then *ite is " << *ite << std::endl;

	std::cout << "Let's test const_iterator " << std::endl;
	ft::List<int>::const_iterator cit = iterator_test.begin();
	std::cout << "The return of *cit, with cit =  list.begin() is : " << *cit << std::endl;
	std::cout << "The return of *(++cit) : " << *(++cit) << std::endl;

	std::cout << "Let's test reverse_iterator" << std::endl;
	std::cout << "Let's test rbegin()" << std::endl;
	ft::List<int>::reverse_iterator rit = iterator_test.rbegin();
	std::cout << "The return of *rit, with rit = list.rbegin() is : " << *rit << std::endl;
	std::cout << " The return of *(++rit) is : " << *(++rit) << std::endl;
	std::cout << "The return of *(rit++) is : " << *(rit++) << " then *rit is : " << *rit << std::endl;
	std::cout << " The return of *(--rit) is : " << *(--rit) << std::endl;
	std::cout << "The return of *(rit--) is : " << *(rit--) << " then *rit is : " << *rit << std::endl;
	std::cout << "Let's test rend()" << std::endl;
	ft::List<int>::reverse_iterator rite = iterator_test.rend();
	std::cout << "The return of *rite, with rite = list.rend() is : " << *rite << std::endl;
	std::cout << " The return of *(++rite) is : " << *(++rite) << std::endl;
	std::cout << "The return of *(rite++) is : " << *(rite++) << " then *rite is : " << *rite << std::endl;
	std::cout << " The return of *(--rite) is : " << *(--rite) << std::endl;
	std::cout << "The return of *(rite--) is : " << *(rite--) << " then *rite is : " << *rite << std::endl;
}

void test_list_int_insert(void) {
	ft::List<int> insert_test;

	std::cout << std::endl << "Test of \033[31;4minsert()\033[0m: " << std::endl;
	create_int_container(&insert_test);
	ft::List<int>::iterator it = insert_test.begin();
	print_list(insert_test);
	std::cout << "Let's try to insert 15 after begin : " << std::endl;
	insert_test.insert(++it, 15);
	print_list(insert_test);
	std::cout << "Let's try to insert 72 at the beginning of the list : " << std::endl;
	insert_test.insert(insert_test.begin(), 72);
	print_list(insert_test);
	std::cout << "Let's try to insert 567 at the end of the list : " << std::endl;
	insert_test.insert(insert_test.end(), 567);
	print_list(insert_test);
}

void test_list_int_erase(void) {
	ft::List<int> erase_test;

	std::cout << std::endl << "Test of \033[31;4merase()\033[0m: " << std::endl;
	create_int_container(&erase_test);
	print_list(erase_test);
	std::cout << "Let's try to use erase on begin() iterator:" << std::endl;
	erase_test.erase(erase_test.begin());
	print_list(erase_test);
	std::cout << "Let's try to use erase on end() iterator:" << std::endl;
	erase_test.erase(erase_test.end());
	print_list(erase_test);
}
void test_list_int_splice(void) {
	ft::List<int> splice_test, other;
	ft::List<int> splice_test2, other2;
	ft::List<int> splice_test3, other3;
	ft::List<int> splice_test4, other4;

	std::cout << std::endl << "Test of \033[31;4msplice()\033[0m: " << std::endl;
	create_int_container(&splice_test);
	other.push_back(123);
	other.push_back(456);
	other.push_back(789);
	print_list(splice_test);
	print_list(other);
	std::cout << "Let's try to use splice to insert at the second list at the begining of the first" << std::endl;
	splice_test.splice(splice_test.begin(), other);
	print_list(splice_test);

	std::cout << "Let's create 2 new lists:" << std::endl;
	create_int_container(&splice_test2);
	other2.push_back(123);
	other2.push_back(456);
	other2.push_back(789);
	print_list(splice_test2);
	print_list(other2);
	std::cout << "Let's try to use splice to insert at the second list at theend of the first" << std::endl;
	splice_test2.splice(splice_test2.end(), other2);
	print_list(splice_test2);

	std::cout << "Let's create 2 new lists:" << std::endl;
	create_int_container(&splice_test3);
	other3.push_back(123);
	other3.push_back(456);
	other3.push_back(789);
	print_list(splice_test3);
	print_list(other3);
	ft::List<int>::iterator it = splice_test3.begin();
	it++;
	std::cout << "Let's try to use splice to insert before the second element: " << std::endl;
	splice_test3.splice(it, other3);
	print_list(splice_test3);

	std::cout << "Let's create 2 new lists:" << std::endl;
	create_int_container(&splice_test4);
	other4.push_back(123);
	other4.push_back(456);
	other4.push_back(789);
	print_list(splice_test4);
	print_list(other4);
	ft::List<int>::iterator it_list = splice_test4.begin();
	ft::List<int>::iterator it_other = other4.begin();
	it_other++;
	it_list++;
	std::cout << "Let's try to use splice to insert the second element of the second list at the second place of the first list O_O " << std::endl;
	splice_test4.splice(it_list, other4, it_other);
	print_list(splice_test4);
	print_list(other4);
}

void test_list_int_max_size(void) {
	ft::List<int> test;

	std::cout << std::endl << "Test of \033[31;4mmax_size()\033[0m: " << std::endl;
	std::cout << test.max_size() << std::endl;
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
	test_list_int_remove();
	test_list_int_swap();
	test_list_int_merge();
	test_list_int_reverse();
	test_list_int_unique();
	test_list_int_sort();
	test_list_int_operator();
	test_list_int_iterator();
	test_list_int_insert();
	test_list_int_erase();
	test_list_int_splice();
	test_list_int_max_size();
}

void test_list(void) {
	std::cout << "Tests with \033[31;1;4mft::List<>\033[0m container: " << std::endl;
	std::srand(time(NULL));
	test_list_int();
}
