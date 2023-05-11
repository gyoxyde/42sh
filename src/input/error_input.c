/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** error_input.c
*/

#include "shell.h"

void error_input(shell_t *shell, char c)
{
    if (c == VEOF) {
        my_eprintf("exit\n");
        exit(shell->exit_code);
    } if (c == EOF) {
        my_eprintf("exit\n");
        exit(shell->exit_code);
    } if (c != '\n' && shell->i->input_str == NULL) {
        my_eprintf("exit\n");
        exit(shell->exit_code);
    } if (shell->i->input_str != NULL) {
        int k = 0;
        for (; k < (int) shell->i->size; k++) {
        }
        shell->i->input_str = realloc(shell->i->input_str, shell->i->size + 1);
        shell->i->input_str[k] = c;
        shell->i->size++;
        shell->i->input_str[k] = '\0';
    }
}
