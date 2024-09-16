CC			=	g++
CXXFLAGS	=	-Wextra -Werror -Wall -std=c++17

SRC			=	test.cpp
NAME		=	test

.PHONY:	all clean re

all:
	$(CC) $(CXXFLAGS) $(SRC) -o $(NAME)

clean:
	rm -rf $(NAME)

re: clean all

