/*
** EPITECH PROJECT, 2022
** upd42sh
** File description:
** ambiguous.c
*/
#include "shell.h"

int ambiguous_error(shell_t *shell, int type, bool *recurs)
{
    if (type == AMBIGUOUS_INPUT) my_eprintf("Ambigous input redirect.\n");
    if (type == AMBIGUOUS_OUTPUT) my_eprintf("Ambigous output redirect.\n");
    if (type == NO_NAME) my_eprintf("Missing name for redirect.\n");

    (*recurs) = false;
    shell->temp_exit_code = 1;
    return 84;
}

int check_for_ambiguous(shell_t *shell, char **array, bool *recurs)
{
    bool isLeftFound = false;
    bool isRightFound = false;

    for (int i = 0; array[i]; i++) {
        if (isLeftFound && (my_strcmp(array[i], "<") == 0
        || my_strcmp(array[i], "<<")) == 0)
            return ambiguous_error(shell, AMBIGUOUS_INPUT, recurs);
        if (isRightFound && (my_strcmp(array[i], ">") == 0
        || my_strcmp(array[i], ">>") == 0 || my_strcmp(array[i], "|") == 0))
            return ambiguous_error(shell, AMBIGUOUS_OUTPUT, recurs);
        if (my_strcmp(array[i], "<") == 0
        || my_strcmp(array[i], "<<") == 0)
            isLeftFound = true;
        if (my_strcmp(array[i], ">") == 0
        || my_strcmp(array[i], ">>") == 0)
            isRightFound = true;
    }
    return 0;
}
