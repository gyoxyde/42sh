/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** error_command.c
*/
#include "shell.h"

void fill_invalid_bool(char **array, int i, bool *invalid, bool *all_invalid)
{
    if (my_strcmp(array[i], "&&") == 0 || my_strcmp(array[i], "||") == 0
        || my_strcmp(array[i], "|") == 0)
        (*invalid) = true;
    else
        (*invalid) = false;
    if (my_strcmp(array[i], "&&") == 0 || my_strcmp(array[i], "||") == 0
    || my_strcmp(array[i], "|") == 0 || my_strcmp(array[i], ";") == 0
    || my_strcmp(array[i], "<") == 0 || my_strcmp(array[i], ">") == 0
    || my_strcmp(array[i], "<<") == 0 || my_strcmp(array[i], ">>") == 0)
        (*all_invalid) = true;
    else
        (*all_invalid) = false;
}

bool check_error_recursive(shell_t *shell, char **array)
{
    bool invalid = false;
    bool all_invalid = false;

    if (my_strcmp(array[0], "|") == 0) {
        my_eprintf("Invalid null command.\n");
        shell->temp_exit_code = 1; return true;
    }
    for (int i = 0; array[i] != NULL; i++) {
        if (all_invalid == true && (my_strcmp(array[i], "&&") == 0
        || my_strcmp(array[i], "||") == 0 || my_strcmp(array[i], "|") == 0)) {
            my_eprintf("Invalid null command.\n");
            shell->temp_exit_code = 1; return true;
        }
        fill_invalid_bool(array, i, &invalid, &all_invalid);
    }
    if (invalid == true) {
        my_eprintf("Invalid null command.\n");
        shell->temp_exit_code = 1; return true;
    }
    return false;
}
