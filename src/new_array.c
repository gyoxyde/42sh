/*
** EPITECH PROJECT, 2023
** new_array.c
** File description:
** new_array.c
*/

#include "shell.h"

char **create_new_array(shell_t *shell, char **temp_array, char **take_com,
                        int count_space)
{
    int size = 0; int save = 0;
    int x = 0; int y = 0;
    for (; temp_array[size] != NULL; size++);
    char **new_array = malloc(sizeof(char *) * (size + count_space + 1));
    for (int i = 0; i < shell->a->save_temp; i++) {
        new_array[y] = my_strdup(temp_array[x]);
        y++;
        x++;
    }
    save = x + 1;
    for (int i = 1; take_com[i] != NULL; i++) {
        new_array[y] = my_strdup(take_com[i]);
        y++;
    }
    for (; temp_array[save] != NULL; save++) {
        new_array[y] = my_strdup(temp_array[save]);
        y++;
    }
    new_array[y] = NULL;
    return new_array;
}

char **create_tab_alias(char *str, char **alias_tab)
{
    alias_tab = malloc (sizeof(char *) * 1 + 1);
    alias_tab[0] = str;
    alias_tab[1] = NULL;
    return alias_tab;
}
