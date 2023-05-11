/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** is_input_tty.c
*/

#include "shell.h"

char *my_getstrtty(shell_t *shell)
{
    char *input_str = NULL;
    size_t size = 0;

    if (getline(&input_str, &size, stdin) == -1) {
        if (isatty(0))
            my_eprintf("exit\n");
        exit(shell->exit_code);
    }
    if (input_str[my_strlen(input_str) - 1] == '\n')
        input_str[my_strlen(input_str) - 1] = '\0';
    return input_str;
}

char *intty_or_not(shell_t *shell)
{
    char *string;
    if (isatty(0) == 0) {
        string = my_getstrtty(shell);
    } else {
        string = my_getstr(shell);
    }
    return string;
}
