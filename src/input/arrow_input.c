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
        printf("\033[2K\r");
        printf("Up arrow pressed\n");
    } if (arrow == 'B') {
        printf("\033[2K\r");
        printf("Down arrow pressed\n");
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
