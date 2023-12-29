/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 19:29:45 by mcutura           #+#    #+#             */
/*   Updated: 2023/10/22 19:29:45 by mcutura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

namespace {
	static int	g_comparisons(0);
}

static size_t	jacobsthal(unsigned int n)
{
	static std::vector<size_t>	jacobsthal_cache;
	if (n < jacobsthal_cache.size()) { return jacobsthal_cache[n]; }
	if (n < 2) {
		jacobsthal_cache.push_back(0);
		jacobsthal_cache.push_back(1);
		return (n == 1);
	}
	size_t const	res(2 * jacobsthal(n - 2) + jacobsthal(n - 1));
	jacobsthal_cache.push_back(res);
	return (jacobsthal_cache[n]);
}

struct Group
{
	int					hi;
	std::vector<Group>	lo;
	Group() {}
	~Group() {}
	Group(int n) : hi(n) {}
	Group(int a, int b) {
		if (a < b) {
			this->hi = b;
			this->lo.push_back(Group(a));
		} else {
			this->hi = a;
			this->lo.push_back(Group(b));
		}
		++g_comparisons;
	}
	Group(Group const &a, Group const &b) {
		if (a.hi < b.hi) {
			this->hi = b.hi;
			this->lo = b.lo;
			this->lo.push_back(a);
		} else {
			this->hi = a.hi;
			this->lo = a.lo;
			this->lo.push_back(b);
		}
		++g_comparisons;
	}
	Group(Group const &a) : hi(a.hi), lo(a.lo) {}
	Group &operator=(Group const &rhs) {
		if (this != &rhs) {
			this->hi = rhs.hi;
			this->lo.clear();
			this->lo = rhs.lo;
		}
		return *this;
	}
	bool operator<(Group const &rhs) const {
		++g_comparisons;
		return (this->hi < rhs.hi);
	}
};

static void	fjmi_sort_vector(std::vector<Group> &groups);

PmergeMe::PmergeMe() : unsorted_()
{}

PmergeMe::~PmergeMe()
{}

void PmergeMe::add(int n)
{
	unsorted_.push_back(n);
}

void PmergeMe::sort(void)
{
	struct timespec	start, end;

	this->create_containers();
	std::cout << "Before:";
	for (std::vector<int>::const_iterator it = unsorted_.begin();
	it != unsorted_.end(); ++it) {
		std::cout << ' ' << *it;
	}
	std::cout << std::endl << "After: ";
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
	this->sort_first();
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);
	for (std::vector<int>::const_iterator it = container1_.begin();
	it != container1_.end(); ++it) {
		std::cout << ' ' << *it;
	}
	std::cout << std::endl
		<< "Time to process a range of " << unsorted_.size()
		<< " elements with std::vector : "
		<< (end.tv_sec - start.tv_sec) * 1000
		+ (end.tv_nsec - start.tv_nsec) / 1000
		<< "us" << std::endl;
	// std::cout << "Comparisons: " << g_comparisons << std::endl;
}

void PmergeMe::create_containers()
{
	this->container1_.reserve(this->unsorted_.size());
	for (std::vector<int>::const_iterator it = this->unsorted_.begin();
	it != this->unsorted_.end(); ++it) {
		this->container1_.push_back(*it);
	}
}

void PmergeMe::sort_first()
{
	std::vector<Group>	groups;

	if (this->container1_.size() < 2) { return; }
	groups.reserve(this->container1_.size());
	for (std::vector<int>::const_iterator it = this->container1_.begin();
	it != this->container1_.end(); ++it) {
		groups.push_back(Group(*it));
	}
	fjmi_sort_vector(groups);
	for (size_t i = 0; i < groups.size(); ++i) {
		this->container1_[i] = groups[i].hi;
	}
}

void PmergeMe::sort_second()
{}

static void	fjmi_sort_vector(std::vector<Group> &groups)
{
	size_t				half(groups.size() >> 1);
	bool				has_straggler(groups.size() & 1);
	Group				straggler;
	std::vector<Group>	pend;

	if (has_straggler) { straggler = groups.back(); }
	if (half < 2U) {
		if (groups.size() > 1 && groups[1] < groups[0]) {
			std::swap(groups[0], groups[1]);
		}
		if (has_straggler && groups[2] < groups[1]) {
			std::swap(groups[2], groups[1]);
			if (groups[1] < groups[0]) {
				std::swap(groups[0], groups[1]);
			}
		}
		return;
	}
	for (size_t i = 0; i < half; ++i) {
		groups[i] = Group(groups[i], groups[i + half]);
	}
	groups.resize(half);
	fjmi_sort_vector(groups);
	pend.reserve(half);
	for (std::vector<Group>::iterator it = groups.begin();
	it != groups.end(); ++it) {
		pend.push_back(it->lo.back());
		it->lo.pop_back();
	}
	groups.reserve((half << 1) + has_straggler);
	groups.insert(groups.begin(), pend.front());
	size_t	insert_mark(0);
	size_t	lookahead(0);
	int		series(3);
	while (insert_mark < pend.size()){
		size_t	idx(jacobsthal(series) - 1);
		if (idx >= pend.size()) { idx = pend.size() - 1; }
		lookahead = insert_mark + idx + 1;
		while (idx > insert_mark) {
			groups.insert(std::upper_bound(
				groups.begin(), groups.begin() + lookahead, pend[idx]),
				pend[idx]);
			--idx;
		}
		insert_mark = jacobsthal(series++) - 1;
	}
	if (has_straggler) {
		groups.insert(std::upper_bound(groups.begin(), groups.end(), straggler),
			straggler);
	}
}
