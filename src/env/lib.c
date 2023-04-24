/*
** EPITECH PROJECT, 2023
** minishell1
** File description:
** lib
*/

#include "../../include/my.h"

int analyse_arg(char *arg, char *command)
{
    int isalpha = my_isalpha(arg);

    if (isalpha == 84 && my_strcmp(command, "setenv")){
        my_error("setenv: Variable name must begin with a letter.\n");
        return 1;
    }
    if (isalpha == 0 && my_strcmp(command, "setenv")){
        my_error
        ("setenv: Variable name must contain alphanumeric characters.\n");
        return 1;
    }
    return 0;
}

void delete_line(int i, var_t m)
{
    if (my_strcmp(m->keys[i], "PWD"))
        m->PWD = -1;
    if (my_strcmp(m->keys[i], "HOME"))
        m->HOME = -1;

    for (; m->env[i + 1]; i++){
        if (my_strcmp(m->keys[i], "PWD"))
            m->PWD -= 1;
        if (my_strcmp(m->keys[i], "HOME"))
            m->HOME -= 1;
        m->env[i] = my_strdup(m->env[i + 1]);
        m->keys[i] = my_strdup(m->keys[i + 1]);
    }
    m->env[i] = NULL;
    m->keys[i] = NULL;
}

int add_line(var_t m, char *arg1, char *arg2)
{
    int tab_len = my_tablen((void **)m->env);

    if (my_strcmp(arg1, "PWD"))
        m->PWD = tab_len;
    if (my_strcmp(arg1, "HOME"))
        m->HOME = tab_len;

    m->keys[tab_len] = my_strdup(arg1);
    m->keys[tab_len + 1] = NULL;
    m->env[tab_len] = my_strcatt(3, arg1, "=", arg2);
    m->env[tab_len + 1] = NULL;
    return 0;
}
