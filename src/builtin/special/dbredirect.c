/*
** EPITECH PROJECT, 2023
** current
** File description:
** dbredirect
*/

#include "../../../include/my.h"

int my_db_redirection(char **args, var_t m)
{
    int i = get_string_index(args, ">");
    if (i == -1)
        return 1;
    char *filename = args[i + 1];
    if (filename == NULL)
        return 1;
    for (int j = i, len = my_tablen((void **)args); j + 1 != len; j++)
        args[j] = args[j + 2];
    if (filename == NULL)
        return 1;
    int fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd == -1){
        strerror(errno);
        return 1;
    }
    return dup_redirection(args, m, fd, 1);
}
