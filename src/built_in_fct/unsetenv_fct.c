/*
** EPITECH PROJECT, 2022
** PROJECTS
** File description:
** unsetenv_fct.c
*/
#include "shell.h"

int unsetenv_fct(shell_t *shell, char **array, int number_av)
{
    if (number_av < 1) {
        write(2, "unsetenv: Too few arguments.\n", 29);
        shell->temp_exit_code = 1;
        return 84;
    }
    for (int x = 1; array[x]; x++) {
        unsetenv_loop(shell, array, x);
    }
    return 0;
}

void unsetenv_loop(shell_t *shell, char **array, int x)
{
    bool unsent_index = false;
    for (int i = 0; shell->env[i]; i++) {
        if (my_strncmp(shell->env[i], array[x], my_strlen(array[x])) == 0) {
            unsent_index = true;
        }
        if (unsent_index == true) {
            shell->env[i] = shell->env[i + 1];
        }
    }
}
