# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/21 02:02:29 by mcutura           #+#    #+#              #
#    Updated: 2024/05/14 18:07:57 by mcutura          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := PmergeMe
SRCS := main.cpp PmergeMe.cpp
OBJS := $(SRCS:%.cpp=%.o)
HDRS := PmergeMe.hpp

CXX := c++
CXXFLAGS := -Wall -Wextra -Werror -std=c++98 -Wpedantic
debug: CXXFLAGS += -ggdb3 -Og
print_comparisons: CPPFLAGS += -DPRINT_COMPARISONS

RM := rm -rf

.PHONY: all clean debug fclean re print_comparisons

all: $(NAME)

$(NAME): $(OBJS) $(HDRS)
	$(CXX) $(OBJS) -o $@

$(OBJS) : %.o : %.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

debug: all

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

print_comparisons: re
