/*
** EPITECH PROJECT, 2023
** check_and_change.c
** File description:
** check tab alias
*/

#include "shell.h"

int alias_exist1(shell_t *shell, char **temp_array, int j)
{
    for (int i = 0; shell->a->file[i] != NULL; i++) {
        char **check_line = my_str_to_word_array(shell->a->file[i], ' ');
        if (my_strcmp(temp_array[j], check_line[0]) == 0 && (j == 0 ||
            my_strcmp(temp_array[j - 1], "&&") == 0 ||
            my_strcmp(temp_array[j - 1], "||") == 0 ||
            my_strcmp(temp_array[j - 1], ";") == 0))
            return 24;
        free(check_line);
    }
    return 0;
}

int alias_exist(shell_t *shell, char **temp_array)
{
    int j = 0;
    for (; temp_array[j] != NULL; j++) {
        if (alias_exist1(shell, temp_array, j) == 24)
            return 24;
    }
    return 0;
}

int check_al_exist(shell_t *shell, char **temp_array)
{
    if (shell->a->file != NULL) {
        if (alias_exist(shell, temp_array) == 24)
            return 24;
    }
    return 0;
}

char **change_array(char **temp_array, shell_t *shell)
{
    shell->a->save_temp = 0;
    shell->a->save_file = 0;
    int count_space = 0;
    char **take_com = NULL;
    char **new_array = NULL;
    find_cor(temp_array, shell);
    take_com = my_str_to_word_array(shell->a->file[shell->a->save_file], ' ');
    for (int i = 1; take_com[i + 1] != NULL; i++)
        count_space++;
    new_array = create_new_array(shell, temp_array, take_com, count_space);
    temp_array = new_array;
    return temp_array;
}

char **def_temp_array(shell_t *shell)
{
    char **temp_array = my_str_to_word_array(shell->str, ' ');
    if (check_al_exist(shell, temp_array) != 24) {
        temp_array = temp_array;
    } else {
        while (check_al_exist(shell, temp_array) == 24)
            temp_array = change_array(temp_array, shell);
    }
    return temp_array;
}
