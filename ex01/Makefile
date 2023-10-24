# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcutura <mcutura@student.42berlin.de>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/21 02:02:29 by mcutura           #+#    #+#              #
#    Updated: 2023/10/21 02:02:29 by mcutura          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# --- Targets ---
NAME := RPN
# --- Sources ---
SRCS := main.cpp RPN.cpp
# --- Objects ---
OBJS := $(SRCS:%.cpp=%.o)
# --- Headers ---
HDRS := RPN.hpp
# --- Compilers ---
CC := cc
CXX := c++
# --- Flags ---
CFLAGS := -Wall -Wextra -Werror -pedantic-errors
debug: CFLAGS += -ggdb3
CXXFLAGS := -Wall -Wextra -Werror -std=c++98 -pedantic-errors
debug: CXXFLAGS += -ggdb3
# --- Utils --
RM := rm -rf

# --- Rules ---
all: $(NAME)

$(NAME): $(OBJS) $(HDRS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@
	
$(OBJS) : %.o : %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

debug: all

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean debug fclean re
