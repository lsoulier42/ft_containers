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

void test_map_insert() {
	ft::Map<std::string, std::string> test_insert;
	std::string strings[10] = {"truc", "bidule", "batman", "robin", "machin", "chose", "la famille adams", "pokemon", "rouge feu", "les simpsons"};

	for (int i = 0; i < 10; i += 2) {
		test_insert.insert(ft::make_pair(strings[i], strings[i + 1]));
	}

	std::cout << test_insert["truc"] << std::endl;
	std::cout << test_insert["batman"] << std::endl;
	std::cout << test_insert["machin"] << std::endl;
	std::cout << test_insert["la famille adams"] << std::endl;
	std::cout << test_insert["rouge feu"] << std::endl;
}

void test_map() {
	test_map_insert();
}
