/*
** EPITECH PROJECT, 2022
** PROJECTS
** File description:
** setenv.c
*/

#include "shell.h"

int setenv_fct(shell_t *shell, char **array, int number_av)
{
    int i = 0; bool isItCreated = false; char *key; char *value; char *temp_str;
    if (number_av > 2) {
        write(2, "setenv: Too many arguments.\n", 28); return 0;
    }
    key = array[1]; value = array[2];
    if (my_getenv(shell->env, key)) isItCreated = true;
    if (isItCreated == false) {
        if (check_key_str(key, shell) != 0) return 84;
        for (; shell->env[i]; i++);
        temp_str = my_strcat(key, "=");
        if (value == NULL)
            shell->env[i] = my_strdup(temp_str);
        else
            shell->env[i] = my_strdup(my_strcat(temp_str, value));
        i++; shell->env[i] = NULL;
    } else
        change_setenv(shell, key, value);
    return 0;
}

int change_setenv(shell_t *shell, char *key, char *value)
{
    char *temp_str;

    for (int i = 0; shell->env[i]; i++) {
        if (my_strncmp(shell->env[i], key, my_strlen(key)) == 0
        && value == NULL) {
            temp_str = my_strcat(key, "=");
            shell->env[i] = my_strdup(temp_str);
        }
        if (my_strncmp(shell->env[i], key, my_strlen(key)) == 0
        && value != NULL) {
            temp_str = my_strcat(key, "=");
            shell->env[i] = my_strdup(my_strcat(temp_str, value));
        }
    }
    return 0;
}

int check_key_str(char *key, shell_t *shell)
{
    if ((key[0] < 'a' || key[0] > 'z') && (key[0] < 'A' || key[0] > 'Z')
    && key[0] != '_') {
        my_eprintf("setenv: Variable name must begin with a letter.\n");
        shell->temp_exit_code = 1;
        return 84;
    }
    for (int i = 1; key[i] != '\0'; i++) {
        if ((key[i] < 'a' || key[i] > 'z') && (key[i] < 'A' || key[i] > 'Z')
        && (key[i] < '0' || key[i] > '9') && (key[i] != '_')) {
            my_eprintf("setenv: Variable name must contain ");
            my_eprintf("alphanumeric characters.\n");
            shell->temp_exit_code = 1;
            return 42;
        }
    }
    return 0;
}
