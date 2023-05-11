/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** backspace_input.c
*/

#include "shell.h"

void backspace(shell_t *shell)
{
    if (shell->i->current_char > 0) {
        printf("\b \b");
        shell->i->current_char--;
        shell->i->size--;
    }
}
