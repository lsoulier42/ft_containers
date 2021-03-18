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
	std::cout << "key: " << root->content.first << " value: " << root->content.second << std::endl;

	if (prev) {
		prev->str = prev_str;
	}
	trunk->str = "   |";

	printTree(root->left, trunk, false);
}

void test_map_insert() {
	ft::Map<std::string, std::string> test_insert;
	std::string strings[10] = {"truc", "bidule", "batman", "robin", "machin", "chose", "la famille adams", "pokemon", "rouge feu", "les simpsons"};

	for (int i = 0; i < 10; i += 2) {
		test_insert.insert(ft::make_pair(strings[i], strings[i + 1]));
	}

	ft::Map<std::string, std::string>::iterator it = test_insert.begin();

	printTree(test_insert.begin()._node, NULL, false);
}

void test_map() {
	test_map_insert();
}
