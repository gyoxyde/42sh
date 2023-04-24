##
## EPITECH PROJECT, 2023
## Makefile
## File description:
## gcc
##

SRC	=	src/main.c	\
		src/shell.c	\
		src/input.c	\
		src/error_handling.c	\
		src/path_handler.c	\
		src/utils.c	\
		src/isitdir.c	\
		src/built_in_fct/fct_main.c	\
		src/built_in_fct/fct_current_dir.c	\
		src/built_in_fct/cd_fct.c	\
		src/built_in_fct/exit_fct.c	\
		src/built_in_fct/setenv_fct.c	\
		src/built_in_fct/unsetenv_fct.c	\
		src/punctuation/clean_separator.c	\
		src/punctuation/semicolon.c	\
		src/punctuation/clean_simpleleft_redi.c	\
		src/punctuation/clean_simpleright_redi.c	\
		src/punctuation/redirection.c	\
		src/punctuation/check_redirection.c	\
		src/punctuation/redirection_main.c	\
		src/punctuation/give_redirection_str.c	\

NAME	=	mysh

OBJ	=	$(SRC:.c=.o)

LIB =	lib/my/libmy.a

LDLIBS = -lmy

LFLAGS = -L lib/my

CFLAGS =	-W -Wall -Wextra -g -lncurses -Iinclude

VALGRIND =	-ggdb3

all:	$(LIB) $(NAME)

$(NAME):	$(OBJ)
	gcc -o $(NAME) $(OBJ) $(LDLIBS) $(LFLAGS) $(CFLAGS)

debug:	$(LIB)
	gcc -o $(NAME) $(SRC) $(LDLIBS) $(LFLAGS) $(CFLAGS) $(VALGRIND) -g

$(LIB):
	$(MAKE) -C lib/my/

clean:
	$(MAKE) -C lib/my/ clean
	rm -rf $(OBJ)

fclean:     clean
	$(MAKE) -C lib/my fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all fclean clean re
