/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 07:47:51 by mcutura           #+#    #+#             */
/*   Updated: 2023/10/21 07:47:51 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOIN_EXCHANGE_HPP
# define BITCOIN_EXCHANGE_HPP

# include <iostream>
# include <fstream>
# include <sstream>
# include <string>
# include <map>

# define DATABASE	"data.csv"

/* --- Error messages --- */
# define USAGE	"Usage: ./btc [path_to_input_file]"
# define EFOPEN	"Error: could not open file"
# define EIHEAD	"Error: invalid header"
# define EDBENT	"Error: database entry misconfigured"
# define EBDATE	"Error: invalid date"
# define EPNUMB	"Error: not a positive number"
# define ELNUMB	"Error: number too large"
# define EBADIN	"Error: bad input"

class BitcoinExchange
{
	public:
		BitcoinExchange();
		BitcoinExchange(BitcoinExchange const &copy);
		BitcoinExchange const &operator=(BitcoinExchange const &rhs);
		~BitcoinExchange();

		int parseDatabase(void);
		void getExchangeRates(char const *input);

	private:
		float getBtcPrice(std::string const &date);
		std::map<std::string, float>	database_;
};

bool	isDateValid(std::string const &date);

#endif // BITCOIN_EXCHANGE_HPP
