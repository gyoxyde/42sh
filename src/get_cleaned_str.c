/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** init
*/

#include "shell.h"

void get_cleaned_str(shell_t *shell)
{
    char *str;
    str = intty_or_not(shell);
    str = clean_str(str);
    str = clean_separator(str);
    str = clean_double_and(str);
    str = clean_right_redi(str);
    str = clean_left_redi(str);
    str = clean_pipe(str);
    shell->str = my_strdup(str);
}

int check_globbings_env(shell_t *shell, char **array)
{
    array = search_special_var(array, shell);
    if (array == NULL)
        return 84;
    array = change_globbings(array, shell);
    if (array == NULL)
        return 84;
    return 0;
}
