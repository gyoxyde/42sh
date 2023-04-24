/*
** EPITECH PROJECT, 2023
** Minishell1
** File description:
** unsetenv
*/

#include "../../include/my.h"

int my_unsetenv(char **args, var_t m)
{
    if (args[0] == NULL || args[0][0] == '\0'){
        my_error("unsetenv: Too few arguments.\n");
        return 1;
    }

    for (int i = 0; args[0]; i++){
        if (!m->env[i]){
            args++;
            i = -1;
            continue;
        }
        if (my_strcmp(m->keys[i], args[0])){
            delete_line(i, m);
            args++;
            i = -1;
            continue;
        }
    }
    return 0;
}
