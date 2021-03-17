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
	const std::string key = std::string("truc");
	const ft::pair<const std::string, std::string> content = ft::make_pair(key, std::string("bidule"));

	test_insert.insert(content);
}

void test_map() {
	test_map_insert();
}
