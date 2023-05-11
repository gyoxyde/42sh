/*
** EPITECH PROJECT, 2022
** Final42sh
** File description:
** utils_env.c
*/
#include "shell.h"

void print_env(char **env)
{
    for (int i = 0; env[i] != NULL; i++)
        my_printf("%s\n", env[i]);
}
