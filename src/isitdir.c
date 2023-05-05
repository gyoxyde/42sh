/*
** EPITECH PROJECT, 2022
** PROJECTS
** File description:
** isItDir.c
*/
#include "shell.h"

int isitdir_exec_cmd(char **array, shell_t *shell, char *path)
{
    struct stat sb;
    stat(path, &sb);
    if (opendir(array[0])) {
        my_eprintf("%s: Permission denied.\n", array[0]);
        shell->temp_exit_code = 1;
        return 84;
    }
    if (access(path, F_OK) != -1 && access(path, X_OK) == -1) {
        my_eprintf("%s: Permission denied.\n", array[0]);
        shell->temp_exit_code = 1;
        return 84;
    }
    return 0;
}
