/*
** EPITECH PROJECT, 2022
** minishell_2
** File description:
** give_redirection_str.c
*/
#include "shell.h"

void check_redirection_two(shell_t *shell, char **array, bool *itIsThere)
{
    if (isitleftredirection(array) == true) {
        for (int i = 0; array[i]; i++) {
            take_redirection_lstr(shell, array, i, "<");
            (*itIsThere) = true;
        }
    }
    if (isitdoubleleftredirection(array) == true) {
        for (int i = 0; array[i]; i++) {
            take_redirection_lstr(shell, array, i, "<<");
            (*itIsThere) = true;
        }
    }
}

bool check_redirection(shell_t *shell, char **array)
{
    shell->redirect_str = NULL;
    shell->redirect_lstr = NULL;
    bool itIsThere = false;

    if (isitrightredirection(array) == true) {
        for (int i = 0; array[i]; i++) {
            take_redirection_str(shell, array, i, ">");
            itIsThere = true;
        }
    }
    if (isitdoublerightredirection(array) == true) {
        for (int i = 0; array[i]; i++) {
            take_redirection_str(shell, array, i, ">>");
            itIsThere = true;
        }
    }
    check_redirection_two(shell, array, &itIsThere);
    if (itIsThere)
        return true;
    return false;
}

void take_redirection_str(shell_t *shell, char **array, int i, char *str)
{
    if (my_strcmp(array[i], str) == 0) {
        if (array[i + 1] == NULL || my_strcmp(array[i + 1], "<") == 0
        || my_strcmp(array[i + 1], "<<") == 0)
            shell->redirect_str = NULL;
        else
            shell->redirect_str = array[i + 1];
    }
}

void take_redirection_lstr(shell_t *shell, char **array, int i, char *str)
{
    if (my_strcmp(array[i], str) == 0) {
        if (array[i + 1] == NULL || my_strcmp(array[i + 1], ">") == 0
        || my_strcmp(array[i + 1], ">>") == 0)
            shell->redirect_lstr = NULL;
        if (array[i + 1] != NULL )
            shell->redirect_lstr = array[i + 1];
    }
}
