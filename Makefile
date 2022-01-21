# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/06 18:21:39 by mrosario          #+#    #+#              #
#    Updated: 2022/01/21 09:13:51 by mrosario         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_container
TESTBIN1 = mytest
TESTBIN2 = stltest

SRCDIR = .
TESTDIR = $(SRCDIR)/testers

GRN = \e[1;32m
RED = \e[1;31m
YEL = \e[1;33m
DEL = \e[2K\r
RST = \e[0m

CXX = clang++

MAIN = $(SRCDIR)/main.cpp
MYTEST = $(SRCDIR)/my_test.cpp
STLTEST = $(SRCDIR)/stl_test.cpp

MAIN_O = $(MAIN:.cpp=.o)
MYTEST_O = $(MYTEST:.cpp=.o)
STLTEST_O = $(STLTEST:.cpp=.o)

SRCFILES =	$(TESTDIR)/tester_utils.cpp \
			$(TESTDIR)/iterator_tester.cpp $(TESTDIR)/my_veritable_vector.cpp \
			$(TESTDIR)/my_magnificent_map.cpp $(TESTDIR)/my_stupendous_stack.cpp \
			$(TESTDIR)/my_superlative_set.cpp $(TESTDIR)/my_talkative_tree.cpp

OBJS = $(SRCFILES:.cpp=.o)

INCLUDES = -I $(SRCDIR)

CXXFLAGS = -Wall -Werror -Wextra -O1 -std=c++98

all: $(NAME)

$(NAME): $(MAIN_O) $(OBJS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -ltermcap -o $(NAME) $(MAIN_O) $(OBJS)

quicktest: $(MYTEST_O) $(STLTEST_O) $(OBJS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -ltermcap -o $(TESTBIN1) $(MYTEST_O) $(OBJS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -ltermcap -o $(TESTBIN2) $(STLTEST_O) $(OBJS)

clean:
	@printf "$(YEL)Deleting object files...$(RST)"
	@rm $(OBJS) $(MAIN_O) $(MYTEST_O) $(STLTEST_O) 2>/dev/null || true
	@printf "$(DEL)$(GRN)Deleted object files\n$(RST)"

fclean: clean
	@printf "$(YEL)Deleting program...$(RST)"
	@rm $(NAME) $(TESTBIN1) $(TESTBIN2) 2>/dev/null || true
	@printf "$(DEL)$(GRN)Deleted program\n$(RST)"

re: fclean all

.PHONY: all clean fclean re
