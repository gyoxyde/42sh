/*
** EPITECH PROJECT, 2022
** minishell_2
** File description:
** semicolon.c
*/
#include "shell.h"

bool fill_array_pipe(shell_t *shell, char **array)
{
    int i = 0;

    shell->array_pipe = malloc(sizeof(char *) * (shell->number_av + 1));
    for (; array[shell->index_array_pipe] != NULL; i++,
    shell->index_array_pipe++) {
        if (my_strcmp(array[shell->index_array_pipe], "|") != 0) {
            shell->array_pipe[i] = my_strdup(array[shell->index_array_pipe]);
        } else {
            shell->array_pipe[i] = NULL;
            shell->index_array_pipe++;
            return true;
        }
    }
    shell->array_pipe[i] = NULL;
    return false;
}

bool fill_array(shell_t *shell, char **array)
{
    int i = 0;
    shell->array = malloc(sizeof(char *) * (shell->number_av + 1));
    for (; array[shell->index_array] != NULL; i++, shell->index_array++) {
        if (my_strcmp(array[shell->index_array], ";") != 0
        && my_strcmp(array[shell->index_array], "||") != 0
        && my_strcmp(array[shell->index_array], "&&") != 0) {
            shell->array[i] = my_strdup(array[shell->index_array]);
        } else {
            shell->array[i] = NULL;
            shell->index_array++;
            return true;
        }
    }
    shell->array[i] = NULL;
    return false;
}
