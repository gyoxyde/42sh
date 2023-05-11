##
## EPITECH PROJECT, 2023
## Makefile
## File description:
## gcc
##

SRC	=	src/main.c	\
		src/shell.c	\
		src/error_handling.c	\
		src/path_handler.c	\
		src/get_cleaned_str.c \
		src/utils.c	\
		src/isitdir.c	\
		src/init.c \
		src/my_asprintf.c \
		src/globbings.c \
		src/search_special_var.c \
		src/built_in_fct/fct_main.c	\
		src/built_in_fct/utils_fct.c	\
		src/built_in_fct/fct_current_dir.c	\
		src/built_in_fct/cd_fct.c	\
		src/built_in_fct/exit_fct.c	\
		src/built_in_fct/setenv_fct.c	\
		src/built_in_fct/unsetenv_fct.c	\
		src/built_in_fct/local.c \
		src/built_in_fct/local_set.c	\
		src/built_in_fct/local_utils.c	\
		src/built_in_fct/local_keys_values.c	\
		src/punctuation/clean/clean_separator.c	\
		src/punctuation/fill_the_arrays.c	\
		src/punctuation/clean/clean_simpleleft_redi.c	\
		src/punctuation/clean/clean_simpleright_redi.c	\
		src/punctuation/redirection/redirection.c	\
		src/punctuation/redirection/check_redirection.c	\
		src/punctuation/redirection/redirection_main.c	\
		src/punctuation/redirection/give_redirection_str.c	\
		src/punctuation/pipe.c	\
		src/punctuation/clean/clean_pipe.c	\
		src/close_fd.c	\
		src/punctuation/clean/clean_separator2.c	\
		src/error_command.c	\
		src/punctuation/redirection/utils_redirection.c	\
		src/punctuation/redirection/ambiguous.c	\
		src/built_in_fct/alias_fct.c \
		src/built_in_fct/check_alias.c \
		src/built_in_fct/alias_one_av.c \
		src/check_and_change.c \
		src/built_in_fct/fct_main_bis.c \
		src/built_in_fct/find_alias.c \
		src/new_array.c \
		src/input/is_input_tty.c \
		src/built_in_fct/unalias_fct.c \
		src/built_in_fct/utils_env.c	\
		src/built_in_fct/echo_fct.c \
		src/punctuation/redirection/error_redirection.c	\
		src/input/history/history.c	\
		src/input/history/history_up.c \
		src/input/input.c	\
		src/input/arrow_input.c	\
		src/input/backspace_input.c	\
		src/input/error_input.c	\
		src/input/history/history_down.c \

NAME	=	42sh

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
	rm -rf .alias .history

re: fclean all

branch:
	@read -p "Enter the branch name: " branch_name && \
	git checkout -b $${branch_name} && \
	git push --set-upstream origin $${branch_name}
	@echo -e "\e[92mBranch created\e[39m"

.PHONY: all fclean clean re
