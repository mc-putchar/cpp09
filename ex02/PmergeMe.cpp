/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 19:29:45 by mcutura           #+#    #+#             */
/*   Updated: 2024/05/14 18:07:04 by mcutura          ###   ########.fr       */
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

////////////////////////////////////////////////////////////////////////////////
// Subclass: Tree

/* Canonical */
Tree::Tree() : root_(0) {}
Tree::~Tree() {}
Tree::Tree(Tree const &rhs) : root_(rhs.root()), subtrees_(rhs.branches()) {}
Tree &Tree::operator=(Tree const &rhs)
{
	if (this != &rhs) {
		this->root_ = rhs.root();
		this->subtrees_ = rhs.branches();
	}
	return *this;
}

/* Additional constructors */
Tree::Tree(int n) : root_(n) {}
Tree::Tree(int a, int b)
{
	if (a < b) {
		this->root_ = b;
		this->subtrees_.push_back(Tree(a));
	} else {
		this->root_ = a;
		this->subtrees_.push_back(Tree(b));
	}
	++g_comparisons;
}

/* Operator overloads */
bool Tree::operator<(Tree const &rhs) const
{
	++g_comparisons;
	return (this->root_ < rhs.root());
}

/* Getters */
int Tree::root() const { return this->root_; }
std::list<Tree> const &Tree::branches() const { return this->subtrees_; }

/* Methods */
void Tree::add_branch(Tree const &branch) { this->subtrees_.push_back(branch); }
Tree Tree::pop_branch(void)
{
	Tree	branch(this->subtrees_.back());
	this->subtrees_.pop_back();
	return branch;
}

/* Static methods */
Tree Tree::convert_to(int n) { return Tree(n); }
int Tree::convert_from(Tree const &tree) { return tree.root(); }

////////////////////////////////////////////////////////////////////////////////
// Substruct: Group

/* Same as Tree, but using std::vector */
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
	static Group convert_to(int n) { return Group(n); }
	static int convert_from(Group const &group) { return group.hi; }
};

static void	fjmi_sort_vector(std::vector<Group> &groups);
static void	fjmi_sort_list(std::list<Tree> &list);

PmergeMe::PmergeMe() : unsorted_() {}

PmergeMe::~PmergeMe() {}

void PmergeMe::add(int n) { unsorted_.push_back(n); }

void PmergeMe::sort(void)
{
	struct timespec	start, end;

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
	std::cout << std::endl;
	std::cout << "Time to process a range of " << unsorted_.size()
		<< " elements with std::vector : "
		<< (end.tv_sec - start.tv_sec) * 1000
		+ (end.tv_nsec - start.tv_nsec) / 1000
		<< "us" << std::endl;
	if (PRINT_COMPARISONS)
		std::cout << "Comparisons: " << g_comparisons << std::endl;
	g_comparisons = 0;
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
	this->sort_second();
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);
	std::cout << "Time to process a range of " << unsorted_.size()
		<< " elements with std::list : "
		<< (end.tv_sec - start.tv_sec) * 1000
		+ (end.tv_nsec - start.tv_nsec) / 1000
		<< "us" << std::endl;
	if (PRINT_COMPARISONS)
		std::cout << "Comparisons: " << g_comparisons << std::endl;
	g_comparisons = 0;

	if (!this->validate()) {
		std::cerr << "ERROR Sorting elements failed" << std::endl;
	}
}

void PmergeMe::sort_first()
{
	std::vector<Group>	groups;

	groups.reserve(this->unsorted_.size());
	std::transform(this->unsorted_.begin(), this->unsorted_.end(),
				std::back_inserter(groups), Group::convert_to);
	fjmi_sort_vector(groups);
	this->container1_.reserve(this->unsorted_.size());
	std::transform(groups.begin(), groups.end(),
				std::back_inserter(this->container1_), Group::convert_from);
}

void PmergeMe::sort_second()
{
	std::list<Tree>	tree;

	std::transform(this->unsorted_.begin(), this->unsorted_.end(),
			std::back_inserter(tree), Tree::convert_to);
	fjmi_sort_list(tree);
	std::transform(tree.begin(), tree.end(),
			std::back_inserter(this->container2_), Tree::convert_from);
}

bool PmergeMe::validate() const
{
	for (std::vector<int>::const_iterator it = this->container1_.begin() + 1;
	it != this->container1_.end(); ++it) {
		if (*it < *(it - 1)) {
			std::cerr << "First container NOT sorted!\nElement: "
			<< *it << " found after " << *(it - 1) << std::endl;
			return false;
		}
	}
	for (std::list<int>::const_iterator it = this->container2_.begin();
	it != this->container2_.end(); ++it) {
		std::list<int>::const_iterator	next(it);
		std::advance(next, 1);
		if (next == this->container2_.end()) { break; }
		if (*next < *it) {
			std::cerr << "Second container NOT sorted!\nElement: "
			<< *next << " found after " << *it << std::endl;
			return false;
		}
	}
	return (this->unsorted_.size() == this->container1_.size()
	&& this->container1_.size() == this->container2_.size());
}

static void	fjmi_sort_vector(std::vector<Group> &groups)
{
	size_t				half(groups.size() >> 1);
	bool				has_straggler(groups.size() & 1);
	Group				straggler;
	std::vector<Group>	pend;

	if (!half) { return; }
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
	pend.reserve(half + has_straggler);
	for (std::vector<Group>::iterator it = groups.begin();
	it != groups.end(); ++it) {
		pend.push_back(it->lo.back());
		it->lo.pop_back();
	}
	if (has_straggler) {
		pend.push_back(straggler);
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
}

/* after all, why not */
static void	binary_inserter(std::list<Tree> &list, size_t end, Tree const &val)
{
	std::list<Tree>::iterator	pos(list.begin());
	size_t						begin(0), mid(0);
	if (end > list.size()) { end = list.size(); }
	while (begin < end) {
		mid = begin + ((end - begin) >> 1);
		std::advance(pos, mid - std::distance(list.begin(), pos));
		if (val < *pos) {
			if (mid == begin) {
				list.insert(pos, val);
				return;
			}
			end = mid - 1;
		} else {
			begin = mid + 1;
		}
	}
	pos = list.begin();
	std::advance(pos, begin);
	if (begin < list.size() && *pos < val) { std::advance(pos, 1); }
	list.insert(pos, val);
}

static void	fjmi_sort_list(std::list<Tree> &list)
{
	size_t const	half(list.size() >> 1);
	bool const		has_straggler(list.size() & 1);
	Tree			straggler;

	if (!half) { return; }
	if (has_straggler) {
		straggler = list.back();
		list.pop_back();
	}
	if (half < 2U) {
		std::list<Tree>::iterator	first(list.begin());
		std::list<Tree>::iterator	second(first);
		std::advance(second, 1);
		if (*second < *first) {
			list.splice(first, list, second);
		}
		if (has_straggler) {
			binary_inserter(list, 1U, straggler);
		}
		return;
	}

	std::list<Tree>::iterator			front(list.begin());
	std::list<Tree>::reverse_iterator	back(list.rbegin());
	size_t								i(0);

	while (i++ < half) {
		if (*front < *back) {
			back->add_branch(*front);
			std::iter_swap(front, back);
		} else {
			front->add_branch(*back);
		}
		std::advance(front, 1);
		std::advance(back, 1);
	}
	list.resize(half);
	fjmi_sort_list(list);

	std::list<Tree>				pend;
	std::list<Tree>::iterator	next(list.begin());
	size_t						done(1U);
	int							series(2);

	list.insert(next, next->pop_branch());
	while (done < list.size()) {
		size_t	offset(jacobsthal(++series));
		if (offset >= list.size()) {
			offset = list.size() - 1;
			if (has_straggler) {
				pend.push_back(straggler);
			}
		}
		std::advance(next, offset - std::distance(list.begin(), next));
		while (std::distance(list.begin(), next) - done) {
			pend.push_back(next->pop_branch());
			std::advance(next, -1);
		}
		done = jacobsthal(series);
	}

	int		count(0);
	int		next_group(2);
	size_t	max_idx(2U);

	series = 3;
	for (std::list<Tree>::const_iterator it = pend.begin();
	it != pend.end(); ++it) {
		binary_inserter(list, max_idx, *it);
		if (++count < next_group) { continue; }
		count = 0;
		max_idx = ((max_idx + 2) << 1) - 2;
		++series;
		next_group = jacobsthal(series) - jacobsthal(series - 1);
	}
}
