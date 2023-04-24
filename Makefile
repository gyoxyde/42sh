##
## EPITECH PROJECT, 2022
## Makefile
## File description:
## Makefile
##

NAME_EXE = mysh

SRC =	$(wildcard src/*.c) $(wildcard src/builtin/*.c) \
		$(wildcard src/env/*.c) $(wildcard src/builtin/special/*.c)

SRC_TEST = $(SRC) /tests/test.c

OBJ	=	$(SRC:.c=.o)

CFLAGS = $(LIB_I_FLAGS) -Wall -Wextra

LIB_I_FLAGS = -I./include/ -L./lib/ -lmy

all: $(NAME_EXE)

clean:
	rm -f $(NAME_EXE)

fclean: clean
	rm -f $(OBJ)
	make -sC lib/printf fclean

$(NAME_EXE):	$(OBJ)
	make -C lib/printf/
	gcc $(OBJ) -o $(NAME_EXE) $(CFLAGS)

debug:
	make re -C lib/printf/
	gcc $(SRC) -g -o $(NAME_EXE) $(CFLAGS)

re: fclean all
