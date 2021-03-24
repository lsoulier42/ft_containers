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

#include <iostream>
#include <string>
#include "test_list.hpp"
#include "test_stack.hpp"
#include "test_queue.hpp"
#include "test_vector.hpp"
#include "test_map.hpp"

int main(int argc, char **argv) {
	std::string containers[5] = {"list", "vector", "map", "stack", "queue"};
	void (*test_functions[5])(void) = {&test_list, &test_vector, &test_map,
		&test_stack, &test_queue};

	if(argc != 2) {
		std::cout << "Usage ./ft_containers <container_name>" << std::endl;
	} else {
		for(size_t i = 0; i < 5; i++) {
			if (argv[1] == containers[i]) {
				test_functions[i]();
				return 0;
			}
		}
		std::cout << "This container is unknown" << std::endl;
	}
	return (0);
}
