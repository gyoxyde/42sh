/*
** EPITECH PROJECT, 2022
** minishell_2
** File description:
** redirection_main.c
*/
#include "shell.h"

bool check_error_redirection(shell_t *shell, char **array, bool *recurs)
{
    if (count_redirections(shell, array, recurs) == 84)
        return true;
    if (check_for_ambiguous(shell, array, recurs) == 84)
        return true;
    return false;
}

int check_missing_name(char **array, int j, bool nulL, bool nulR)
{
    if (nulL || nulR)
        if (array[j + 1] == NULL
        || my_strcmp(array[j + 1], "<") == 0
        || my_strcmp(array[j + 1], "<<") == 0
        || my_strcmp(array[j + 1], ">") == 0
        || my_strcmp(array[j + 1], ">>") == 0)
            return 84;
    return 0;
}

int count_redirections(shell_t *shell, char **array, bool *recurs)
{
    bool checkForNulL = false;
    bool checkForNulR = false;

    for (int j = 0; array[j] != NULL; j++) {
        checkForNulL = false;
        checkForNulR = false;
        if (my_strcmp(array[j], ">") == 0 || my_strcmp(array[j], ">>") == 0)
            checkForNulR = true;
        if (my_strcmp(array[j], "<") == 0 || my_strcmp(array[j], "<<") == 0)
            checkForNulL = true;
        if (check_missing_name(array, j, checkForNulL, checkForNulR) == 84)
            return ambiguous_error(shell, NO_NAME, recurs);
    }
    return 0;
}
