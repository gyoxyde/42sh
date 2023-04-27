/*
** EPITECH PROJECT, 2022
** minishell_2
** File description:
** semicolon.c
*/
#include "minishell_2.h"

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

// void create_array_for_semicolon(shell_t *shell, char **array, int number_av)
// {
//     shell->array = malloc(sizeof(char *) * (number_av + 1));
//     for (int i = 0; array[i]!= NULL; i++) {
//         if (array[i][0] == ';')
//             for (int a = 0; array[i][a] == ';'; a++);
//         for (int j = 0; array[shell->index_array][j] != '\0'; j++) {
//             for (int k = 0; array[shell->index_array][j + k] == ';') {
//                 shell->index_array++;
//             return true;
//             }
//         }
//     }
//     return false;
// }
