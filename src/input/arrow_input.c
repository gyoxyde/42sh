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
    if (arrow == 'A') {
        history_up(shell);
    } if (arrow == 'B') {
        history_down(shell);
    } if (arrow == 'D') {
        if (shell->i->current_char > 0) {
            shell->i->current_char--;
            printf("\033[1D");
        }
    } if (arrow == 'C') {
        if (shell->i->current_char < (int) shell->i->size) {
            shell->i->current_char++;
            printf("\033[1C");
        }
    }
}
