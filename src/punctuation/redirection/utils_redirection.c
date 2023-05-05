/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** utils_redirection.c
*/
#include "shell.h"

int dup_redirection(char **args, shell_t *shell, int fd, int copy_fd)
{
    int saved_stdout = dup(copy_fd);
    int number_av = shell->number_av;

    if (saved_stdout == -1) {
        perror("dup");
        return 84;
    } if (dup2(fd, copy_fd) == -1) {
        perror("dup2");
        return 84;
    }
    shell->isLeftDupDone = true;
    shell_redirection(shell, args, number_av);
    if (dup2(saved_stdout, copy_fd) == -1) {
        perror("dup2");
        return 84;
    }
    close(saved_stdout);
    close(fd);
    return 0;
}
