/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_map.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louise <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 11:46:44 by louise            #+#    #+#             */
/*   Updated: 2021/03/13 11:46:45 by louise           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_map.hpp"

struct Trunk
{
	Trunk *prev;
	std::string str;

	Trunk(Trunk *prev, std::string str)
	{
		this->prev = prev;
		this->str = str;
	}
};

void showTrunks(Trunk *p)
{
	if (p == NULL) {
		return;
	}

	showTrunks(p->prev);
	std::cout << p->str;
}

void printTree(ft::bstree<ft::pair<const std::string, std::string> >* root, Trunk *prev, bool isLeft)
{
	if (root == NULL) {
		return;
	}

	std::string prev_str = "    ";
	Trunk *trunk = new Trunk(prev, prev_str);

	printTree(root->right, trunk, true);

	if (!prev) {
		trunk->str = "———";
	}
	else if (isLeft)
	{
		trunk->str = ".———";
		prev_str = "   |";
	}
	else {
		trunk->str = "`———";
		prev->str = prev_str;
	}

	showTrunks(trunk);
	std::cout << root->content.first << std::endl;

	if (prev) {
		prev->str = prev_str;
	}
	trunk->str = "   |";

	printTree(root->left, trunk, false);
	delete trunk;
}

template<class Key, class T>
void printState(const ft::Map<Key, T>& test_map) {
	printTree(test_map.begin()._node, NULL, false);
	std::cout << "current \033[30;4msize()\033[0m: " << test_map.size() << std::endl;
	std::cout << "the return of \033[30;4mempty()\033[0m: " << verbose_bool(test_map.empty()) << std::endl;
}

void test_map_whole() {
	ft::Map<std::string, std::string> test_insert;
	std::string strings[] = {"truc", "bidule", "batman", "robin", "machin", "chose",
		"la famille adams", "pokemon", "rouge feu", "les simpsons", "ululu", "bidule",
		"wtf", "nausicaa", "show", "me the money", "anna", "montana"};
	int arrSize = *(&strings + 1) - strings;
	ft::pair<ft::Map<std::string, std::string>::iterator, bool> test_return;

	std::cout << "This test will focus on \033[31;1;4minsert()\033[0m:" << std::endl;
	std::cout << "Let's create a map with using this array of strings:" << std::endl;
	for (int i = 0; i < arrSize; i += 2) {
		std::cout << "\"" << strings[i] << "\" => \"" << strings[i + 1] << "\"" << std::endl;
	}

	for (int i = 0; i < arrSize; i += 2) {
		test_return = test_insert.insert(ft::make_pair(strings[i], strings[i + 1]));
		std::cout << "the key : \"" << test_return.first->first;
		std::cout << "\" with value: \"" << test_return.first->second << "\"";
		std::cout << (test_return.second ? " has been created" : " cannot be created") << std::endl;
	}

	test_return = test_insert.insert(ft::make_pair(strings[0], strings[1]));
	std::cout << "the key : \"" << test_return.first->first;
	std::cout << "\" with value: \"" << test_return.first->second << "\"";
	std::cout << (test_return.second ? " has been created" : " cannot be created") << std::endl;

	printState(test_insert);

	std::cout << std::endl << "This test will focus on \033[31;1;4miterators\033[0m:" << std::endl;
	ft::Map<std::string, std::string>::iterator it = test_insert.begin();
	while (it != test_insert.end())
	{
		std::cout << "return of it: " << it->first << std::endl;
		it++;
	}

	std::cout << std::endl << "This test will focus on \033[31;1;4mclear()\033[0m:" << std::endl;
	test_insert.clear();
	printState(test_insert);
}

void test_map() {
	std::cout << std::endl << "Test for the container \033[31;1;4mMap\033[0m:" << std::endl;
	test_map_whole();
}
