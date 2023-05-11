/*
** EPITECH PROJECT, 2022
** PROJECTS
** File description:
** fct_current_dir.c
*/
#include "shell.h"

int fct_curr_dir(char **array, shell_t *shell)
{
    pid_t pid;

    if (isitdir_exec_cmd(array, shell, array[0]) != 0)
        return 84;
    pid = fork();
    if (pid == 0) {
        exec_child_process(shell, array, array[0]);
    } else {
        if (pid > 0) {
            exec_parent_process(shell, array);
        } else {
        perror("fork");
        exit(84);
        }
    }
    return 0;
}

int check_segfault(int status)
{
    if (status == 139) {
        my_printf("Segmentation fault");
        if (__WCOREDUMP(status) != 0) {
            my_printf(" (core dumped)");
        }
        my_printf("\n");
    }
    return 0;
}

int check_curr_dir(char *str)
{
    bool isThereBackslash = false;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '/') {
            isThereBackslash = true;
        }
    }
    if (isThereBackslash == true) {
        return 1;
    }
    return 0;
}

void check_errno(char **array)
{
    if (errno == 8)
        my_eprintf("%s: Exec format error. Wrong Architecture.\n", array[0]);
    else
        my_eprintf("%s: Command not found.\n", array[0]);
}
