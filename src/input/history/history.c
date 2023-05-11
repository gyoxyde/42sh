/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** history.c
*/

#include "shell.h"

void history_add(shell_t *shell)
{
    if (shell->i->input_str == NULL || shell->i->input_str[0] == '\0' ||
    (shell->i->history_length > 0 &&
    strcmp(shell->i->input_str, shell->i->history[shell->i->history_length - 1])
    == 0)) {
        return;
    }
    if (shell->i->history_length == HISTORY_SIZE) {
        free(shell->i->history[0]);
        for (int j = 1; j < HISTORY_SIZE - 1; j++) {
            shell->i->history[j] = shell->i->history[j + 1];
        }
        shell->i->history_length--;
    }
    shell->i->history[shell->i->history_length++] = strdup(shell->i->input_str);
}
