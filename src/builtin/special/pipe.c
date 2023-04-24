/*
** EPITECH PROJECT, 2023
** current
** File description:
** dbredirect
*/

#include "../../../include/my.h"

static char **get_pipe_command(char **args)
{
    int i = 0;
    char **command = malloc(sizeof(char *) * (my_tablen((void **)args) + 1));

    for (i = 0; args[i] != NULL && !if_in(args[i], "|"); i++)
        command[i] = args[i];
    command[i] = NULL;
    return command;
}

int my_pipe(char **args, var_t m)
{
    char **command;
    command = get_pipe_command(args);
    args = args + my_tablen((void **)command) + 1;
    dup2(m->pipefd[1], 1);
    m->return_value = search_know_command(command, m);
    close(m->pipefd[1]);
    dup2(m->pipefd[0], 0);
    m->return_value = search_know_command(args, m);
    close(m->pipefd[0]);
    return m->return_value;
}
    // dup2(fd[1], 1);
    // search_know_command(command, m);
    // close(fd[1]);
    // my_error("here\n");
    // dup2(fd[0], 0);
    // int return_value = search_know_command(args, m);
    // close(fd[0]);
    // return return_value;
// }
