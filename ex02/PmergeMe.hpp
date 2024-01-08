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

/* Chef Martin's recipe for Ford-Johnson algorithm (aka merge-insertion sort)
 *
 * A hybrid of merge sort and binary insertion sort, this algorithm aims to
 * minimize the number of comparisons performed while sorting elements
 *
 * Simplified instructions:
	1. Pair up (leave the odd egg out)
	2. sort in pairs
	3. sort pairs recursively by their higher value in ascending sequence
	4. insert lower values into sequence using Jacobsthal numbers to select
		those which would require minimal possible range of comparisons
	5. drop in that odd egg if any
	6. place in oven for maximum (nlog(n)-n) comparisons before serving
	7. enjoy your sorted sequence
 *
 * This implementation compares performance of two variants:
	1. using ONLY std::vector as container to sort
	2. using ONLY std::list as container to sort
 * Timed results serve to indicate performance of operations used on containers
 */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <algorithm>
# include <ctime>
# include <iostream>
# include <list>
# include <vector>

class Tree
{
	public:
		Tree();
		~Tree();
		Tree(int n);
		Tree(int a, int b);
		Tree(Tree const &rhs);

		Tree &operator=(Tree const &rhs);
		bool operator<(Tree const &rhs) const;

		int root() const;
		std::list<Tree> const &branches() const;
		void add_branch(Tree const &branch);
		Tree pop_branch(void);

		static Tree convert_to(int n);
		static int convert_from(Tree const &tree);

	private:
		int				root_;
		std::list<Tree>	subtrees_;
};

class PmergeMe
{
	public:
		PmergeMe();
		~PmergeMe();

		void add(int n);
		void sort(void);

	private:
		void sort_first();
		void sort_second();
		bool validate() const;

		std::vector<int>	unsorted_;
		std::vector<int>	container1_;
		std::list<int>		container2_;

		/* = deleted */
		PmergeMe(PmergeMe const &other);
		PmergeMe const &operator=(PmergeMe const &rhs);
};

#endif  // PMERGEME_HPP
