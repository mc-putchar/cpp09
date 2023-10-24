/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 22:10:32 by mcutura           #+#    #+#             */
/*   Updated: 2023/10/21 22:10:32 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <exception>

#include "RPN.hpp"

# define USAGE	"Usage: ./RPN \"expression with postfix notation\""

int	main(int ac, char **av)
{
	if (ac != 2) {
		std::cerr << USAGE << std::endl;
		return 1;
	}

	int	res(0);
	try {
		res = RPN::calculate(av[1]);
	} catch (std::exception &ex) {
		std::cerr << ex.what() << std::endl;
		return 1;
	}
	std::cout << res << std::endl;
	return 0;
}
