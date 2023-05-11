/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** history_up.c
*/

#include "shell.h"

void history_up_set_value(shell_t *shell)
{
    printf("%s", shell->i->history[shell->i->history_index]);
    free(shell->i->input_str);
    shell->i->input_str = malloc(sizeof(char) + 1);
    memset(shell->i->input_str, 0, 0);
    shell->i->input_str =
    strdup(shell->i->history[shell->i->history_index]);
    shell->i->current_char = strlen(shell->i->input_str);
    shell->i->size = strlen(shell->i->input_str);
}

void history_up(shell_t *shell)
{
    char prompt[PATH_MAX];
    if (shell->i->history_index > 0 &&
    shell->i->history[shell->i->history_index - 1] != NULL) {
        if (shell->i->history_index != 0)
            shell->i->history_index--;
        printf("\033[2K\r");
        if (getcwd(prompt, sizeof(prompt)) != NULL)
            printf("[%s] ", prompt);
        history_up_set_value(shell);
    }
}
