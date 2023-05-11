/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** arrow_input.c
*/

#include "shell.h"

void arrow(shell_t *shell)
{
    getchar();
    int arrow = getchar();
    if (arrow == 'A')
        history_up(shell);
    if (arrow == 'B')
        history_down(shell);
}
