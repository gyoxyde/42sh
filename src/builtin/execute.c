/*
** EPITECH PROJECT, 2023
** minishell1
** File description:
** execute
*/

#include "../../include/my.h"

static int execute_slash(var_t m, char *command, char **args)
{
    int exec = 0;

    if (access(command, F_OK) == 1)
        return command_not_found(1, command);

    exec = execve(command, args, m->env);
    if (exec != -1)
        return (char)exec;

    return command_not_found(1, command);
}

static int execute_here(var_t m, char *command, char **args)
{
    char *path = my_strcatt(3, m->env[m->PWD] + 4, "/", command);
    int exec = 0;

    if (access(path, F_OK) == 1)
        return command_not_found(1, command);
    exec = execve(path, args, m->env);
    if (exec != -1)
        return (char)exec;

    return command_not_found(1, command);
}

static int execute_path(var_t m, char *command, char **args)
{
    char *path;
    int exec = 0;
    errno = 0;

    for (int i = 0; m->path[i]; i++){
        path = my_strcatt(3, m->path[i], "/", command);
        if (access(path, F_OK) == 1)
            continue;
        exec = execve(path, args, m->env);
        if (exec != -1)
            return exec;
    }
    command_not_found(-1, command);
    return 1;
}

int command_not_found(int a, char *command)
{
    my_error(command);
    my_error(": Command not found.\n");

    if (a == -1)
        exit(-1);
    if (a == 1)
        return 1;
    return 0;
}

int my_execute(char **args, var_t m)
{
    char *command = my_strdup(args[0]);

    if (m->path[0] == NULL || args[0][0] == ' ' || args[0][0] == '\0')
        return 0;

    if (command[0] == '/')
        return execute_slash(m, command, args);

    for (int i = 0; command[i]; i++)
        if (command[i] == '/')
            return execute_here(m, command, args);

    return execute_path(m, command, args);
}
