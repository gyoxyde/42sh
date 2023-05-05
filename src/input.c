/*
** EPITECH PROJECT, 2022
** PROJECTS
** File description:
** input.c
*/
#include "42sh.h"

char *my_getstr(shell_t *shell)
{
    char *input_str = NULL;
    size_t size = 0;
    if (getline(&input_str, &size, stdin) == -1) {
        my_eprintf("exit\n");
        exit(shell->exit_code);
    }
    if (input_str[my_strlen(input_str) - 1] == '\n')
        input_str[my_strlen(input_str) - 1] = '\0';
    return input_str;
}
