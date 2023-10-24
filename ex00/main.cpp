/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 07:36:58 by mcutura           #+#    #+#             */
/*   Updated: 2023/10/21 07:36:58 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#include "BitcoinExchange.hpp"

int	main(int ac, char **av)
{
	if (ac != 2) {
		std::cerr << USAGE << std::endl;
		return 1;
	}

	BitcoinExchange newFTX;

	if (newFTX.parseDatabase())
		return 1;
	newFTX.getExchangeRates(av[1]);

	return 0;
}
