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
#include <map>
#include <utility>

void test_map_insert() {
	ft::Map<const char*, const char*> test_insert;
	//ft::pair<const char*, char*> test_pair = ft::make_pair("truc", "bidule");
	//std::map<const char*, const char*> test_insert;

	test_insert["truc"] = "bidule";
	std::cout << test_insert["truc"] << std::endl;
}

void test_map() {
	test_map_insert();
}
