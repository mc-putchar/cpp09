/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 20:51:02 by mcutura           #+#    #+#             */
/*   Updated: 2023/10/21 20:51:02 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int RPN::calculate(char const *args)
{
	std::stack<int>	expr;

	while (*args) {
		if (*args != ' ') {
			if (std::isdigit(*args)) {
				expr.push(*args - '0');
			} else {
				if (expr.size() < 2)
					throw RPNGenericError();
				int tmp = expr.top();
				expr.pop();
				switch (*args) {
					case '+':
						tmp += expr.top();
						break;
					case '-':
						tmp = expr.top() - tmp;
						break;
					case '*':
						tmp *= expr.top();
						break;
					case '/':
						if (!tmp)
							throw RPNDivideByZero();
						tmp = expr.top() / tmp;
						break;
					default:
						throw RPNGenericError();
						break;
				}
				expr.pop();
				expr.push(tmp);
			}
		}
		++args;
	}
	if (expr.empty())	throw RPNGenericError();
	return (expr.top());
}

const char* RPN::RPNDivideByZero::what() const throw()
{
	return "Error: division by zero";
}

const char* RPN::RPNGenericError::what() const throw()
{
	return "Error";
}
