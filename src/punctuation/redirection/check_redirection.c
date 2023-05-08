/*
** EPITECH PROJECT, 2022
** minishell_2
** File description:
** check_redirection.c
*/
#include "shell.h"

bool isitrightredirection(char **array)
{
    bool check_started = false;

    for (int i = 0; array[i] != NULL; i++) {
        if (my_strcmp(array[i], ">") == 0) {
            check_started = true;
        }
        if (array[i + 1] != NULL && check_started == true) {
            return true;
        }
    }
    return false;
}

bool isitdoublerightredirection(char **array)
{
    bool check_started = false;

    for (int i = 0; array[i] != NULL; i++) {
        if (my_strcmp(array[i], ">>") == 0)
            check_started = true;
        if (array[i + 1] != NULL && check_started == true)
            return true;
    }
    return false;
}

bool isitleftredirection(char **array)
{
    bool check_started = false;

    for (int i = 0; array[i] != NULL; i++) {
        if (my_strcmp(array[i], "<") == 0)
            check_started = true;
        if (array[i + 1] != NULL && check_started == true)
            return true;
    }
    return false;
}

bool isitdoubleleftredirection(char **array)
{
    bool check_started = false;

    for (int i = 0; array[i] != NULL; i++) {
        if (my_strcmp(array[i], "<<") == 0)
            check_started = true;
        if (array[i + 1] != NULL && check_started == true)
            return true;
    }
    return false;
}
