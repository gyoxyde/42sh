/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** utils_redirection.c
*/
#include "shell.h"

int write_double_left_pipe(shell_t *shell, int *pipefd, char *file)
{
    file = get_heredoc(shell->redirect_lstr, shell);
    if (pipe(pipefd) == -1)
        return 84;
    write(pipefd[1], file, my_strlen(file));
    if (close(pipefd[1]) == 84) {
        perror("close");
        return 84;
    }
    shell->isLeftDupDone = true;
    return 0;
}

int redi_error_message(int type, shell_t *shell, char *str)
{
    if (type == NO_NAME) my_eprintf("Missing name for redirect.\n");
    if (type == NO_FILE) my_eprintf("%s: No such file or directory.\n", str);
    if (type == NOT_DIR) my_eprintf("%s: Not a directory.\n", str);
    if (type == PERM_DENIED) my_eprintf("%s: Permission denied.\n", str);
    if (type == INVALID_CMD) my_eprintf("Invalid null command.\n");
    if (type == NO_DUP2) perror("dup2");

    shell->temp_exit_code = 1;
    return 84;
}

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
