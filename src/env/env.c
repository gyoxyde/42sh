/*
** EPITECH PROJECT, 2023
** minishell1
** File description:
** env
*/

#include "../../include/my.h"

int my_env(__attribute__((unused)) char **args, var_t m)
{
    for (int i = 0; m->env[i]; i++){
        my_putstr(m->env[i]);
        write(1, "\n", 1);
    }
    return 0;
}
