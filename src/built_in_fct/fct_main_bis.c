/*
** EPITECH PROJECT, 2023
** fct_main_bis.c
** File description:
** fct_main_bis
*/

#include "shell.h"

int check_built_in_fct2(char *str)
{
    if (!my_strcmp(str, "unset")) return UNSET;
    if (!my_strcmp(str, "set")) return SET;
    if (!my_strcmp(str, "exit")) return EXIT;
    if (!my_strncmp(str, "./", 2)) return EXECUTE;
    if (check_curr_dir(str)) return EXECUTE_CURR_DIR;
    return NOT_BUILT_IN;
}
