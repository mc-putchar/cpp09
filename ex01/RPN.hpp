/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 20:22:16 by mcutura           #+#    #+#             */
/*   Updated: 2023/10/21 20:22:16 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
# define RPN_HPP

# include <iostream>
# include <stack>
# include <sstream>
# include <exception>
# include <cctype>

class RPN
{
	public:
		static int calculate(char const *args);

		class RPNDivideByZero : public std::exception
		{
			virtual const char* what() const throw();
		};
		class RPNGenericError : public std::exception
		{
			virtual const char* what() const throw();
		};

	private:
		RPN();
		RPN(RPN const &other);
		RPN const &operator=(RPN const &rhs);
		~RPN();
};

#endif  // RPN_HPP
