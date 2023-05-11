/*
** EPITECH PROJECT, 2023
** alias_one_av.c
** File description:
** alias_one_av
*/

#include "shell.h"

void print_com(shell_t *shell)
{
    int pos = 0;
    int size = strlen(shell->array[1]);
    for (; my_strncmp(shell->array[1], shell->a->file[pos], size) != 0; pos++);
    char **com = my_str_to_word_array(shell->a->file[pos], ' ');
    for (int i = 1; com[i] != NULL; i++) {
        printf("%s ", com[i]);
    }
    printf("\n");
}

void alias_one_av(shell_t *shell)
{
    if (check_alias_exist(shell) == 24)
        print_com(shell);
}
