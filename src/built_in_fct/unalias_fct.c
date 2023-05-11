/*
** EPITECH PROJECT, 2023
** unalias.c
** File description:
** unalias
*/

#include "shell.h"

int check_exist(shell_t *shell, int i)
{
    char **com = NULL;
    for (int j = 0; shell->a->file[j] != NULL; j++) {
        com = my_str_to_word_array(shell->a->file[j], ' ');
        if (my_strcmp(shell->array[i], com[0]) == 0)
            return 24;
    }
    return 0;
}

void supp_line(shell_t *shell, int i)
{
    char **new_array = NULL;
    char **com = NULL;
    int size = 0;
    int x = 0;
    for (; shell->a->file[size] != NULL; size++);
    new_array = malloc(sizeof(char *) * size);
    for (int j = 0; shell->a->file[j] != NULL; j++) {
        com = my_str_to_word_array(shell->a->file[j], ' ');
        if (my_strcmp(shell->array[i], com[0]) != 0) {
            new_array[x] = my_strdup(shell->a->file[j]);
            x++;
        }
    }
    new_array[x] = NULL;
    shell->a->file = new_array;
}

void check_and_supp(shell_t *shell, int i)
{
    if (check_exist(shell, i) == 24) {
        supp_line(shell, i);
    }
}

void unalias_function(shell_t *shell)
{
    int i = 1;
    if (shell->a->file != NULL) {
        for (; shell->array[i] != NULL; i++) {
            check_and_supp(shell, i);
        }
    }
}
