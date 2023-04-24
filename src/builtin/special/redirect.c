/*
** EPITECH PROJECT, 2023
** current
** File description:
** dbredirect
*/

#include "../../../include/my.h"

int dup_redirection(char **args, var_t m, int fd, int copy_fd)
{
    int saved_stdout = dup(copy_fd);
    int return_value;

    if (saved_stdout == -1) {
        perror("dup");
        return 1;
    }
    if (dup2(fd, copy_fd) == -1) {
        perror("dup2");
        return 1;
    }
    return_value = search_know_command(args, m);
    if (dup2(saved_stdout, copy_fd) == -1) {
        perror("dup2");
        return 1;
    }
    close(saved_stdout);
    close(fd);
    return return_value;
}

int get_string_index(char **args, char *str)
{
    int i = 0;

    for (i = 0; args[i] != NULL; i++) {
        if (if_in(args[i], str))
            return i;
    }
    return -1;
}

int my_redirection(char **args, var_t m)
{
    char *filename;
    int i = get_string_index(args, ">");
    if (i == -1)
        return 1;
    filename = args[i + 1];
    for (int j = i, len = my_tablen((void **)args); j + 1 != len; j++)
        args[j] = args[j + 2];
    if (filename == NULL)
        return 1;
    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1){
        strerror(errno);
        return 1;
    }
    return dup_redirection(args, m, fd, 1);
}
