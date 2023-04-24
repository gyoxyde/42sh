/*
** EPITECH PROJECT, 2023
** minishell2
** File description:
** *
*/

#include "../include/my.h"

static int (*execute[])(char **, var_t) = {
    &my_exit, &my_cd, &my_env, &my_setenv, &my_unsetenv,
    &my_redirection, &my_db_redirection, &my_input, &my_db_input, &my_other};


void pipe_child(var_t m, char **commands, pipes_t p, char **args)
{
    char *commandss[] = {"exit", "cd", "env", "setenv", "unsetenv",
        ">", ">>", "<", "<<", NULL};
    if (p->prev_fd[0])
        dup2(p->prev_fd[0], STDIN_FILENO);
    if (commands[p->i + 1])
        dup2(p->fd[1], STDOUT_FILENO);
    close(p->fd[0]);
    close(p->fd[1]);
    close(p->prev_fd[0]);
    close(p->prev_fd[1]);
    for (int j = 0; j < 5; j++)
        if (my_strcmp(args[0], commandss[j]))
            exit(execute[j]((++args), m));
    exit(my_execute(args, m));
}

void pipe_parent(pipes_t p)
{
    if (p->prev_fd[0]) {
        close(p->prev_fd[0]);
    }
    if (p->prev_fd[1]) {
        close(p->prev_fd[1]);
    }
    p->prev_fd[0] = p->fd[0];
    p->prev_fd[1] = p->fd[1];
    p->i++;
    return;
}

void pipe_fork(var_t m, char **commands, pipes_t p)
{
    if (pipe(p->fd) == -1) {
        perror("pipe failed");
        exit(EXIT_FAILURE);
    }
    char **args = to_word_array(commands[p->i], ' ');
    pid_t pid = fork();
    if (pid == -1) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    } else if (pid == 0)
        pipe_child(m, commands, p, args);
    else {
        pipe_parent(p);
        return;
    }
}

int close_all(var_t m, pipes_t p)
{
    close(p->prev_fd[0]);
    close(p->prev_fd[1]);
    close(p->fd[0]);
    close(p->fd[1]);

    int wstatus;
    while ((waitpid(-1, &wstatus, 0)) > 0) {
        if (WIFEXITED(wstatus)) {
            p->status = WEXITSTATUS(wstatus);
        }
    }
    dup2(p->old_stdin, STDIN_FILENO);
    dup2(p->old_stdout, STDOUT_FILENO);
    close(p->old_stdin);
    close(p->old_stdout);
    m->return_value = p->status;
    return p->status;
}

int create_pipe(char *command, var_t m)
{
    char **commands = to_word_array(command, '|');
    for (int i = 0; commands[i]; i++) {
        commands[i] = my_cleanstr(commands[i]);
    }
    pipes_t p = malloc(sizeof(struct my_pipes));
    p->i = 0;
    p->status = 0;
    p->fd = malloc(sizeof(int) * 2);
    p->prev_fd = malloc(sizeof(int) * 2);
    p->prev_fd[0] = 0;
    p->prev_fd[1] = 0;
    p->old_stdin = dup(STDIN_FILENO);
    p->old_stdout = dup(STDOUT_FILENO);
    while (commands[p->i])
        pipe_fork(m, commands, p);
    return close_all(m, p);
}
