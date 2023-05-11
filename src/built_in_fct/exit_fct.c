/*
** EPITECH PROJECT, 2022
** PROJECTS
** File description:
** exit_fct.c
*/
#include "shell.h"

int exit_fct(int number_av, shell_t *shell, char **array)
{
    if (number_av != 0) {
        if (number_av > 1 || check_number_exit(shell, array) == 84) {
            my_eprintf("exit: Expression Syntax.\n");
            shell->temp_exit_code = 1;
            return 84;
        }
        if (check_number_exit(shell, array) == 42) {
            my_eprintf("exit: Badly formed number.\n");
            shell->temp_exit_code = 1;
            return 42;
        }
        my_printf("exit\n");
        free(shell->a->file);
        exit(shell->exit_code);
    } else {
    my_printf("exit\n");
    free(shell->a->file);
    exit(0);
    }
}

int check_number_exit(shell_t *shell, char **array)
{
    if (array[1][0] < '0' || array[1][0] > '9')
        return 84;
    for (int i = 0; array[1][i] != '\0'; i++) {
        if (array[1][i] < '0' || array[1][i] > '9')
            return 42;
    }
    shell->exit_code = my_getnbr(array[1]);
    return 0;
}
