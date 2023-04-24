##
## EPITECH PROJECT, 2022
## Makefile
## File description:
## Makefile
##

NAME_LIB = libmy.a

SRC_PRINTF =	./my_if.c \
		./my_print_base.c \
		./my_print_str.c \
		./my_print_unsigned_arg.c \
		./my_printf.c \
		./my_print_p.c \
		./my_print_g.c \
		./my_print_float.c \
		./my_opti.c \
		./my_print_gbis.c \
		./my_put_nbr.c \
		./my_putchar.c \
		./my_putstr.c \
		./my_revstr.c \
		./my_intlen.c \
		./my_strcat.c \
		./my_strlen.c \
		./my_compute_power_rec.c \
		./my_lib.c \
		./l_list.c \
		./my_error.c \
		./my_lib2.c \
		./my_lib3.c \
		./garbage_collector.c \
		./garbage_llist.c \
		./search_in_str.c \

OBJ	=	$(SRC_PRINTF:.c=.o)

CFLAGS = -Wall -Wextra $(I_FLAGS)

I_FLAGS = -I./include

all: $(NAME_LIB)

clean:
	rm -f ../$(NAME_LIB)
	rm -f $(NAME_LIB)

fclean: clean
	rm -f $(OBJ)

$(NAME_LIB):	$(OBJ)
	ar rc $(NAME_LIB) $(OBJ)
	cp $(NAME_LIB) ../$(NAME_LIB)
	cp my_printf.h ../../include/
	cp garbage.h ../../include

debug:
	gcc -g -o $(NAME_LIB) $(C_FLAGS) $(SRC_SRC_LIB) $(I_FLAGS)

re: fclean all
