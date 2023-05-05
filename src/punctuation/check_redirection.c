/*
** EPITECH PROJECT, 2022
** minishell_2
** File description:
** check_redirection.c
*/
#include "42sh.h"

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

// void check_redirection_right(shell_t *shell, char *array)
// {
//     if (isitrightredirection(shell, array) == true) {
//         return;
//         open_simple_right(shell, array);
//     }
//     if (isitdoublerightredirection(shell, array) == true)
//         open_double_right(shell, array);
// }

//order:
// CHECK_RIGHT && CHECK_DOUBLE_RIGHT. if yes then check double right when open()
    // else
    // do the rest of the loop:
    // check_left_redirection -> check_ pipe.
