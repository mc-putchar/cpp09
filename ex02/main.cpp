/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 19:30:18 by mcutura           #+#    #+#             */
/*   Updated: 2023/10/22 19:30:18 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <sstream>

#include "PmergeMe.hpp"

#define USAGE	"Usage:\t./PmergeMe [1 .. n]\n \
\t./PmergeMe `shuf -i 1-100000 -n 3000 | tr '\\n' ' '`"

static bool	onlydigits(char *str);

int	main(int ac, char **av)
{
	PmergeMe			pmm;
	std::istringstream	ss;

	if (ac < 2) {
		std::cerr << USAGE << std::endl;
		return 1;
	}
	for (int i = 1; i < ac; ++i) {
		ss.str(av[i]);
		int n;
		ss >> n;
		if (ss.fail() || !onlydigits(av[i])) {
			std::cerr << "Error" << std::endl;
			return 1;
		}
		ss.clear();
		pmm.add(n);
	}
	pmm.sort();
	return 0;
}

static bool	onlydigits(char *str)
{
	while (*str) {
		if (*str < '0' || *str > '9')	return false;
		++str;
	}
	return true;
}
