/*
** EPITECH PROJECT, 2022
** Final42sh
** File description:
** error_redirection.c
*/

#include "shell.h"

int error_redirection(shell_t *shell, int type)
{
    if (type == RIGHT_REDI)   my_eprintf("Invalid null command.\n");
    if (type == LEFT_REDI)  my_eprintf("Ambiguous input redirect.\n");

    shell->temp_exit_code = 1;
    return 84;
}

int check_pipe_redirection(shell_t *shell, char **array,
char *redirection, int type_error)
{
    bool isPipeThere = false;

    for (int i = 0; array[i] != NULL; i++) {
        if (isPipeThere == true && !my_strcmp(array[i], redirection))
            return error_redirection(shell, type_error);
        isPipeThere = false;
        if (!my_strcmp(array[i], "|"))
            isPipeThere = true;
    }
    return 0;
}
