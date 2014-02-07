# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kube <kube@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2013/12/03 17:38:57 by cfeijoo           #+#    #+#              #
#    Updated: 2014/02/04 17:18:57 by kube             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = get_next_line

LIBNAME = ft
LIBFOLDER = ./libft
INCFOLDER = ./libft/includes

SRC	= get_next_line.c
OSRC = $(SRC:.c=.o)

TESTFILE = test.c
OTESTFILE = $(TESTFILE:.c=.o)
TESTNAME = test_gnl

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

clean:
	if [ -f $(OSRC) ]; \
		then /bin/rm -f $(OSRC); \
	fi

fclean: clean
	if [ -f $(TESTNAME) ]; \
		then /bin/rm -f $(TESTNAME); \
	fi

re: fclean $(NAME)

retest: fclean test
