/*
** EPITECH PROJECT, 2023
** minishell1
** File description:
** setenv
*/

#include "../../include/my.h"

int my_setenv(char **args, var_t m)
{
    char *arg2;
    char *arg1;
    if (args[0] == NULL || args[0][0] == '\0')
        return my_env(args, m);
    if (my_tablen((void **)args) > 2){
        my_error("setenv: Too many arguments.\n");
        return 1;
    }
    arg1 = my_strdup(args[0]);
    arg2 = (!args[1]) ? my_strdup("\0") : my_strdup(args[1]);
    if (analyse_arg(arg1, "setenv") == 1)
        return 1;
    if (my_strcmp(arg1, "PATH"))
        m->path = to_word_array(arg2, ':');
    for (int i = 0; m->env[i]; i++)
        if (my_strcmp(arg1, m->keys[i])){
            m->env[i] = my_strcatt(3, m->keys[i], "=", arg2);
            return 0;
        }
    return add_line(m, arg1, arg2);
}
