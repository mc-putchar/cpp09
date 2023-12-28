/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 13:39:43 by mcutura           #+#    #+#             */
/*   Updated: 2023/10/21 13:39:43 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()	{}

BitcoinExchange::~BitcoinExchange()	{}

int BitcoinExchange::parseDatabase(std::string const &db_file)
{
	std::string			line;
	std::istringstream	ss;
	std::ifstream		dataFile(db_file.c_str());

	if (!dataFile.is_open()) {
		std::cerr << EFOPEN << std::endl;
		return 1;
	}
	if (!std::getline(dataFile, line) || line.compare(DBHEADER)) {
		std::cerr << EIHEAD << std::endl;
		return 1;
	}

	while (std::getline(dataFile, line)) {
		std::string::size_type	pos(line.find(","));
		if (pos == std::string::npos) {
			std::cerr << EDBENT << std::endl;
			return 1;
		}

		std::string				key(line.substr(0, pos));
		if (!isDateValid(key)) {
			std::cerr << EBADAY << std::endl;
		}

		float	value;
		ss.str(line.substr(pos + 1));
		ss >> value;
		if (ss.fail()) {
			std::cerr << EBADIN << std::endl;
			return 1;
		}
		ss.clear();
		database_[key] = value;
	}
	return 0;
}

void BitcoinExchange::getExchangeRates(char const *input) const
{
	std::string			line;
	std::istringstream	ss;
	std::ifstream		inputFile(input);

	if (!inputFile.is_open()) {
		std::cerr << EFOPEN << std::endl;
		return ;
	}
	if (!std::getline(inputFile, line) || line.compare(INHEADER)) {
		std::cerr << EIHEAD << std::endl;
		return ;
	}

	while (std::getline(inputFile, line)) {
		size_t		pos(line.find(FIELDSEP));
		if (pos == std::string::npos) {
			std::cerr << EDBENT << std::endl;
			continue ;
		}

		std::string	date(line.substr(0, pos));
		if (!isDateValid(date)) {
			std::cerr << EBADAY << std::endl;
			continue ;
		}

		float	value;
		ss.str(line.substr(pos + 3));
		ss >> value;
		if (ss.fail()) {
			std::cerr << EBADIN << std::endl;
			ss.clear();
			continue ;
		}
		ss.clear();
		if (value < 0) {
			std::cerr << ENEGNO << std::endl;
			continue ;
		}
		if (value > 1000) {
			std::cerr << EOVERF << std::endl;
			continue ;
		}
		float price = this->getBtcPrice(date);
		std::cout << date << " => "
			<< value << " = " << value * price << std::endl;
	}
}

float BitcoinExchange::getBtcPrice(std::string const &date) const
{
	typedef std::map<std::string, float>::const_iterator MapIterator;
	MapIterator	it(this->database_.lower_bound(date));
	if (it == this->database_.end()
	|| (date.compare(it->first) && it != this->database_.begin()))
		return (--it)->second;
	return it->second;
}

static inline bool	isLeapYear(int yy)
{
	return (!((yy & 3) || (yy % 100 && !(yy % 400))));
}

bool	isDateValid(std::string const &date)
{
	size_t				start, end;
	int					year, month, day;
	std::istringstream	ss;

	end = date.find("-");
	if (end == std::string::npos)
		return false;
	ss.str(date.substr(0, end));
	ss >> year;
	if (ss.fail() || year < 0 || year > 9999)
		return false;
	ss.clear();
	start = end + 1;
	end = date.find("-", start);
	if (end == std::string::npos)
		return false;
	ss.str(date.substr(start, end));
	ss >> month;
	if (ss.fail() || month < 1 || month > 12)
		return false;
	ss.clear();
	ss.str(date.substr(end + 1));
	ss >> day;
	if (ss.fail() || day < 1 || day > 31)
		return false;
	if ((day == 31 && (month == 4 || month == 6 || month == 9 || month == 11))
	|| (month == 2 && (day > 29 || (day == 29 && !isLeapYear(year)))))
		return false;
	return true;
}
