/*
** EPITECH PROJECT, 2023
** check_alias.c
** File description:
** check_alias
*/

#include "shell.h"

int check(shell_t *shell)
{
    for (int i = 0; shell->a->file[i] != NULL; i++) {
        char **com = my_str_to_word_array(shell->a->file[i], ' ');
        if (my_strcmp(shell->array[1], com[0]) == 0)
            return 24;
    }
    return 0;
}

int check_alias_exist(shell_t *shell)
{
    if (shell->a->file != NULL) {
        if (check(shell) == 24)
            return 24;
    }
    return 0;
}
