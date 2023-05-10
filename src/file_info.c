/*
** EPITECH PROJECT, 2022
** struct
** File description:
** my_struct
*/

#include "shell.h"

int how_many_letter(char *pathfile)
{
    int i = 0;
    int fd_sec;
    char buf[1];

    fd_sec = open(pathfile, O_RDONLY);
    if (fd_sec == -1) {
        return 84;
    }
    for (; read(fd_sec, buf, 1) != 0; i++);
    close(fd_sec);
    return i;
}

char *new_string(char *buffer)
{
    int i = 0;
    char *new_str = malloc(sizeof(char) * (strlen(buffer) + 2));

    for (; buffer[i] != '\0'; i++) {
        new_str[i] = buffer[i];
    }
    new_str[i] = '\n';
    new_str[i + 1] = '\0';
    return new_str;
}

void check_backslash(shell_t *shell)
{
    for (int i = 0; shell->a->contenu[i] != '\0'; i++) {
        if (shell->a->contenu[i] != '\n' && shell->a->contenu[i + 1] == '\0')
            shell->a->contenu = new_string(shell->a->contenu);
    }
}

int file_info(char *pathfile, shell_t *shell)
{
    int i = 0;
    int fd;
    char buf[1];

    shell->a->pathfile = pathfile;
    if (how_many_letter(pathfile) == 84)
        return 84;
    shell->a->number_letter = how_many_letter(pathfile);
    shell->a->contenu = malloc(sizeof(char) * (shell->a->number_letter + 1));
    fd = open(pathfile, O_RDONLY);
    for (i = 0; read(fd, buf, 1) != 0; i++)
        shell->a->contenu[i] = buf[0];
    shell->a->contenu[i] = '\0';
    check_backslash(shell);
    shell->a->file = my_str_to_word_array(shell->a->contenu, '\n');
    close(fd);
    return 0;
}
