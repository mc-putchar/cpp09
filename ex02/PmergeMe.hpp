/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 22:57:20 by mcutura           #+#    #+#             */
/*   Updated: 2023/10/21 22:57:20 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <algorithm>
# include <ctime>
# include <iostream>
# include <list>
# include <vector>

class PmergeMe
{
	public:
		PmergeMe();
		~PmergeMe();

		void add(int n);
		void sort(void);

	private:
		void create_containers();
		void sort_first();
		void sort_second();

		std::vector<int>	unsorted_;
		std::vector<int>	container1_;
		std::list<int>		container2_;

		/* = deleted */
		PmergeMe(PmergeMe const &other);
		PmergeMe const &operator=(PmergeMe const &rhs);
};

#endif  // PMERGEME_HPP
