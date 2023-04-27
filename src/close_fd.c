/*
** EPITECH PROJECT, 2022
** 42shtest
** File description:
** close_fd.c
*/
#include "minishell_2.h"

void close_all_fd(shell_t *shell, char **array, int number_av)
{
    if (shell->isLeftDupDone == true) {
        if (dup2(shell->fd2, 0) < 0) {
            perror("dup2"); return;
        } if (close(shell->fd2) == -1) {
            perror("close"); return;
        }
    }
    if (shell->isRightDupDone == true) {
        if (dup2(shell->fd, 1) < 0) {
            perror("dup2"); return;
        } if (close(shell->fd) == -1) {
            perror("close"); return;
        } return;
    }
    if (shell->recurs_pipe == true) {
        shell_do_fct(shell, array, number_av);
    }
    if (shell->hasBeenPiped == true)
        if (shell->array_pipe[shell->index_array_pipe] == NULL)
            close_all(shell);
}
