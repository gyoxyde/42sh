/*
** EPITECH PROJECT, 2022
** 42shtest
** File description:
** pipe.c
*/
#include "shell.h"

void pipe_child(shell_t *shell)
{
    if (shell->recurs_pipe == false && shell->hasBeenPiped == false)
        return;
    if (shell->isLeftDupDone == false) {
        if (shell->p->prev_fd[0])
            dup2(shell->p->prev_fd[0], STDIN_FILENO);
        if (shell->recurs_pipe == true)
            dup2(shell->p->fd[1], STDOUT_FILENO);
        close(shell->p->fd[0]);
        close(shell->p->fd[1]);
        close(shell->p->prev_fd[0]);
        close(shell->p->prev_fd[1]);
    } else {
        if (shell->recurs_pipe == true)
            dup2(shell->p->fd[1], STDOUT_FILENO);
        close(shell->p->fd[0]);
    }
}

void pipe_parent(shell_t *shell)
{
    if (shell->recurs_pipe == false && shell->hasBeenPiped == false)
        return;
    if (shell->isLeftDupDone == false) {
        if (shell->p->prev_fd[0]) {
            close(shell->p->prev_fd[0]);
        }
        if (shell->p->prev_fd[1]) {
            close(shell->p->prev_fd[1]);
        }
    }
    if (shell->isLeftDupDone == true) {
        dup2(shell->p->fd[0], STDIN_FILENO);
        close(shell->p->fd[1]);
        close(shell->p->fd[0]);
    }
    shell->p->prev_fd[0] = shell->p->fd[0];
    shell->p->prev_fd[1] = shell->p->fd[1];
    return;
}

int close_all(shell_t *shell)
{
    int wstatus;

    close(shell->p->prev_fd[0]);
    close(shell->p->prev_fd[1]);
    close(shell->p->fd[0]);
    close(shell->p->fd[1]);

    while ((waitpid(-1, &wstatus, WUNTRACED)) > 0) {
        if (WIFEXITED(wstatus)) {
            shell->temp_exit_code = WEXITSTATUS(wstatus);
        }
    }
    dup2(shell->p->old_stdin, STDIN_FILENO);
    dup2(shell->p->old_stdout, STDOUT_FILENO);
    close(shell->p->old_stdin);
    close(shell->p->old_stdout);
    check_error_segfault(wstatus, shell);
    return shell->temp_exit_code;
}

int pipe_loop(char **array, shell_t *shell)
{
    shell->recurs_pipe = false;

    if (my_strcmp(array[0], "|") == 0) {
        my_eprintf("Invalid null command.\n");
        shell->temp_exit_code = 1;
        return -1;
    }
    if (fill_array_pipe(shell, array) == true) {
        if (pipe(shell->p->fd) == -1) {
        perror("pipe failed");
        exit(EXIT_FAILURE);
        }
        array = shell->array_pipe;
        shell->recurs_pipe = true;
        shell->hasBeenPiped = true;
    } else {
    array = shell->array_pipe;
    }
    return 0;
}

int create_pipe(shell_t *shell)
{
    shell->p->status = 0;
    shell->index_array_pipe = 0;
    shell->array_pipe = NULL;
    shell->p->fd = malloc(sizeof(int) * 2);
    shell->p->prev_fd = malloc(sizeof(int) * 2);
    shell->p->prev_fd[0] = 0;
    shell->p->prev_fd[1] = 0;
    shell->p->old_stdin = dup(STDIN_FILENO);
    shell->p->old_stdout = dup(STDOUT_FILENO);
    return 0;
}
