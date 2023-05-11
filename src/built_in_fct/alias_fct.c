/*
** EPITECH PROJECT, 2023
** alias_fct.c
** File description:
** alias function
*/

#include "shell.h"

int check_which_alias(int number_av, char *str)
{
    if (my_strcmp(str, "alias") == 0) {
        if (number_av == 1)
            return 13;
        else
            return 12;
    }
    return 0;
}

void alias_no_av_fct(shell_t *shell)
{
    if (shell->a->file != NULL) {
        for (int i = 0; shell->a->file[i] != NULL; i++) {
            my_printf("%s\n", shell->a->file[i]);
        }
    }
}

void alias_existing(shell_t *shell, int size_line, int save, int pos)
{
    for (; shell->a->file[pos] != NULL; pos++) {
        char **com = my_str_to_word_array(shell->a->file[pos], ' ');
        if (my_strcmp(com[0], shell->array[1]) == 0)
            save = pos;
    }
    char *str = malloc (sizeof(char) * (size_line + shell->a->count + 1));
    for (int i = 1; shell->array[i] != NULL; i++) {
        if (i > 1)
            str = my_strcat(str, " ");
        str = my_strcat(str, shell->array[i]);
    }
    shell->a->file[save] = str;
}

void alias_not_existing(shell_t *shell, int size_line)
{
    int length = 0;
    int y = 0;
    char **alias_tab = NULL;
    char *str = malloc(sizeof(char) * (size_line + shell->a->count + 1));
    memset(str, 0, (size_line + shell->a->count));
    for (int i = 1; shell->array[i] != NULL; i++) {
        if (i > 1)
            str = my_strcat(str, " ");
        str = my_strcat(str, shell->array[i]);
    }
    if (shell->a->file != NULL) {
        for (; shell->a->file[length] != NULL; length++);
        alias_tab = malloc (sizeof(char *) * length + 2);
        for (; shell->a->file[y] != NULL; y++)
            alias_tab[y] = my_strdup(shell->a->file[y]);
        alias_tab[y] = str; alias_tab[y + 1] = NULL;
    } else {
        alias_tab = create_tab_alias(str, alias_tab);
    }
    shell->a->file = alias_tab;
}

void alias_fct(shell_t *shell)
{
    shell->a->count = 0;
    int size_line = 0;
    int save = 0;
    int pos = 0;
    for (int i = 1; shell->array[i] != NULL; i++)
        size_line += strlen(shell->array[i]);
    for (int i = 1; shell->array[i] != NULL; i++)
        shell->a->count++;
    if (check_alias_exist(shell) == 24) {
        alias_existing(shell, size_line, save, pos);
    } else {
        alias_not_existing(shell, size_line);
    }
}
