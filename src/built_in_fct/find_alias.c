/*
** EPITECH PROJECT, 2023
** find_alias.c
** File description:
** find_alias
*/

#include "shell.h"

void find_cor1(char **temp_array, shell_t *shell, int j)
{
    for (int i = 0; shell->a->file[i] != NULL; i++) {
        char **check_line = my_str_to_word_array(shell->a->file[i], ' ');
        if (my_strcmp(temp_array[j], check_line[0]) == 0 && (j == 0 ||
            my_strcmp(temp_array[j - 1], "&&") == 0 ||
            my_strcmp(temp_array[j - 1], "||") == 0 ||
            my_strcmp(temp_array[j - 1], ";") == 0)) {
            shell->a->save_file = i;
            shell->a->save_temp = j;
        }
        free(check_line);
    }
}

void find_cor(char **temp_array, shell_t *shell)
{
    int j = 0;
    for (; temp_array[j] != NULL; j++) {
        find_cor1(temp_array, shell, j);
    }
}
