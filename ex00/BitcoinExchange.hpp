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
# include <map>
# include <sstream>
# include <string>

/* predefined constants */
# define DBHEADER	"date,exchange_rate"
# define INHEADER	"date | value"
# define FIELDSEP	" | "

/* --- Error messages --- */
# define USAGE	"Usage: ./btc [path_to_input_file]"
# define EFOPEN	"Error: could not open file"
# define EIHEAD	"Error: invalid header"
# define EDBENT	"Error: database entry misconfigured"
# define EBADAY	"Error: invalid date"
# define ENEGNO	"Error: not a positive number"
# define EOVERF	"Error: number too large"
# define EBADIN	"Error: bad input"

class BitcoinExchange
{
	public:
		BitcoinExchange();
		~BitcoinExchange();

		int parseDatabase(std::string const &db_file);
		void getExchangeRates(char const *input) const;

	private:
		std::map<std::string, float>	database_;
		float getBtcPrice(std::string const &date) const;

		/* deleted - our exchange cannot be copied */
		BitcoinExchange(BitcoinExchange const &copy);
		BitcoinExchange const &operator=(BitcoinExchange const &rhs);
};

bool	isDateValid(std::string const &date);

#endif // BITCOIN_EXCHANGE_HPP
