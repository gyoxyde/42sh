/*
** EPITECH PROJECT, 2023
** alias_fct.c
** File description:
** alias function
*/

#include "shell.h"

int check_which_alias(int number_av, char *str)
{
    if (my_strcmp(str, "alias") == 0) {
        if (number_av == 1)
            return 13;
        else
            return 12;
    }
    return 0;
}

void alias_no_av_fct(shell_t *shell)
{
    file_info(".alias", shell);
    if (shell->a->file != NULL) {
        for (int i = 0; shell->a->file[i] != NULL; i++) {
            my_printf("%s\n", shell->a->file[i]);
        }
    }
}

void alias_existing(shell_t *shell, int size_line, int save, int pos)
{
    int size = strlen(shell->array[1]);
    for (; my_strncmp(shell->array[1], shell->a->file[pos], size) != 0; pos++);
    save = pos;
    char *str = malloc (sizeof(char) * (size_line + shell->a->count + 1));
    for (int i = 1; shell->array[i] != NULL; i++) {
        if (i > 1)
            str = my_strcat(str, " ");
        str = my_strcat(str, shell->array[i]);
    }
    shell->a->file[save] = str;
    int fd2 = open(".alias",  O_WRONLY | O_CREAT | O_TRUNC, 0644);
    for (int i = 0; shell->a->file[i] != NULL; i++) {
        write(fd2, shell->a->file[i], strlen(shell->a->file[i]));
        write(fd2, "\n", 1);
    }
    close(fd2);
}

void alias_not_existing(shell_t *shell)
{
    int fd = open(".alias",  O_WRONLY | O_CREAT | O_APPEND, 0644);
    for (int i = 1; shell->array[i] != NULL; i++) {
        write(fd, shell->array[i], strlen(shell->array[i]));
        if (i < shell->a->count)
            write(fd, " ", 1);
        else
            write(fd, "\n", 1);
    }
    close(fd);
}

void alias_fct(shell_t *shell)
{
    shell->a->count = 0;
    int size_line = 0;
    int save = 0;
    int pos = 0;
    file_info(".alias", shell);
    for (int i = 1; shell->array[i] != NULL; i++)
        size_line += strlen(shell->array[i]);
    for (int i = 1; shell->array[i] != NULL; i++)
        shell->a->count++;
    if (check_alias_exist(shell) == 24) {
        alias_existing(shell, size_line, save, pos);
    } else {
        alias_not_existing(shell);
    }
}
