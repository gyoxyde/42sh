/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** init
*/

#include "42sh.h"

void get_cleaned_str(shell_t *shell)
{
    char *str;
    str = my_getstr(shell);
    str = clean_str(str); str = clean_separator(str);
    str = clean_double_and(str);
    str = clean_right_redi(str); str = clean_left_redi(str);
    str = clean_pipe(str);
    shell->str = my_strdup(str);
}
