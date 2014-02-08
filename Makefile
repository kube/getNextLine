# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kube <kube@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2013/12/03 17:38:57 by cfeijoo           #+#    #+#              #
#    Updated: 2014/02/08 15:06:42 by kube             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = get_next_line

LIBNAME = ft
LIBFOLDER = ./libft
INCFOLDER = ./libft/includes

SRC	= get_next_line.c
OSRC = $(SRC:.c=.o)

FORUMFILE	= get_next_line_forum.c
FORUMOBJECT = $(FORUMFILE:.c=.o)

TESTFILE = test.c
OTESTFILE = $(TESTFILE:.c=.o)
TESTNAME = test_gnl

FORUMTESTFILE = test_forum.c
FORUMTESTOBJECT = $(FORUMTESTFILE:.c=.o)
FORUMTESTNAME = test_gnl_forum

CFLAGS = -Wall -Wextra -Werror
CC = /usr/bin/gcc

ifeq ($(GDB), 1)
	CFLAGS += -g
endif

$(NAME):
	$(CC) -c -I$(INCFOLDER) $(SRC) $(CFLAGS)

test: $(NAME)
	$(CC) -c -I$(INCFOLDER) $(TESTFILE) $(CFLAGS)
	$(CC) -o $(TESTNAME) -L$(LIBFOLDER) -l$(LIBNAME) $(OTESTFILE) $(OSRC)

forum:
	$(CC) -c -I$(INCFOLDER) $(FORUMFILE) $(CFLAGS)
	$(CC) -c -I$(INCFOLDER) $(FORUMTESTFILE) $(CFLAGS)
	$(CC) -o $(FORUMTESTNAME) -L$(LIBFOLDER) -l$(LIBNAME) $(FORUMTESTOBJECT) $(FORUMOBJECT)

clean:
	rm -f $(OSRC)
	rm -f $(FORUMOBJECT)

fclean: clean
	rm -f $(TESTNAME)
	rm -f $(FORUMTESTNAME)

re: fclean $(NAME)

retest: fclean test
