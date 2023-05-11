/*
** EPITECH PROJECT, 2022
** 42shtest
** File description:
** close_fd.c
*/
#include "shell.h"

void close_all_fd(shell_t *shell, char **array, int number_av)
{
    int status;

    if (shell->hasBeenPiped == true && shell->recurs_pipe == false) {
            close_all(shell);
            return;
    }
    if (shell->recurs_pipe == true) {
        shell_do_fct(shell, array, number_av);
    }
    if (shell->hasBeenPiped == false) {
        wait(&status);
        check_error_segfault(status, shell);
    }
}

int close_right_fd(shell_t *shell)
{
    if (shell->isRightDupDone == true) {
        if (dup2(shell->fd, 1) < 0) {
            perror("dup2");
            return 84;
        }
        if (close(shell->fd) == -1) {
            perror("close");
            return 84;
        }
    }
    return 0;
}
