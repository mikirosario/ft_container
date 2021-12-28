# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mikiencolor <mikiencolor@student.42.fr>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/06 18:21:39 by mrosario          #+#    #+#              #
#    Updated: 2021/12/28 00:31:38 by mikiencolor      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_container

SRCDIR = .

GRN = \e[1;32m
RED = \e[1;31m
YEL = \e[1;33m
DEL = \e[2K\r
RST = \e[0m

CXX = clang++

SRCFILES = $(SRCDIR)/main.cpp

OBJS = $(SRCFILES:.cpp=.o)

INCLUDES = -I $(SRCDIR)

CXXFLAGS = -Wall -Werror -Wextra -g -std=c++98

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -ltermcap -o $(NAME) $(OBJS)

clean:
	@printf "$(YEL)Deleting object files...$(RST)"
	@rm $(OBJS) 2>/dev/null || true
	@printf "$(DEL)$(GRN)Deleted object files\n$(RST)"

fclean: clean
	@printf "$(YEL)Deleting program...$(RST)"
	@rm $(NAME) 2>/dev/null || true
	@printf "$(DEL)$(GRN)Deleted program\n$(RST)"

re: fclean all

.PHONY: all clean fclean re
