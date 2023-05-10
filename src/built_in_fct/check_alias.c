/*
** EPITECH PROJECT, 2023
** check_alias.c
** File description:
** check_alias
*/

#include "shell.h"

int check(shell_t *shell)
{
    int line = strlen(shell->array[1]);
    for (int i = 0; shell->a->file[i] != NULL; i++) {
        if (my_strncmp(shell->array[1], shell->a->file[i], line) == 0)
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
