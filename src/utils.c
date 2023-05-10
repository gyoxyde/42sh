/*
** EPITECH PROJECT, 2022
** PROJECTS
** File description:
** utils.c
*/
#include "shell.h"

int count_av(char *str)
{
    int space_count = 0;
    for (int x = 0; str[x] != '\0'; x++) {
        if (str[x] == ' ')
            space_count++;
    }
    return space_count;
}

int get_avnb(shell_t *shell, char **array, int *number_av)
{
    if (isitrightredirection(array) == true) {
        if (shell->redirect_str != NULL)
            (*number_av) = (*number_av) - 1;
        (*number_av) = (*number_av) - 1;
    } if (isitdoublerightredirection(array) == true) {
        if (shell->redirect_str != NULL)
            (*number_av) = (*number_av) - 1;
        (*number_av) = (*number_av) - 1;
    } if (isitleftredirection(array) == true) {
        if (shell->redirect_lstr != NULL)
            (*number_av) = (*number_av) - 1;
        (*number_av) = (*number_av) - 1;
    } if (isitdoubleleftredirection(array) == true) {
        if (shell->redirect_lstr != NULL)
            (*number_av) = (*number_av) - 1;
        (*number_av) = (*number_av) - 1;
    }
    return (*number_av);
}

char *my_getenv(char **env, char *key)
{
    for (int i = 0; env[i]; i++) {
        if (my_strncmp(env[i], key, my_strlen(key)) == 0)
            return &env[i][my_strlen(key) + 1];
    }
    return NULL;
}

int change_oldpwd(shell_t *shell)
{
    char *key = "OLDPWD=";
    if (shell->wasItCd == false)
        return 84;
    if (my_getenv(shell->env, "OLDPWD") == NULL) {
        change_setenv(shell, "OLDPWD", shell->oldpwd);
        return 0;
    }
    for (int i = 0; shell->env[i] != NULL; i++) {
        if (my_strncmp(shell->env[i], "OLDPWD", 6) == 0) {
            key = my_strcat(key, shell->oldpwd);
            shell->env[i] = my_strdup(key);
        }
    }
    return 0;
}

int prompt(shell_t *shell)
{
    int i = 0; char *key = "PWD="; char prompt[PATH_MAX];
    if (isatty(0) == 1) {
        if (getcwd(prompt, sizeof(prompt)) != NULL) {
            my_printf("[%s] ", prompt);
            shell->temp_oldpwd = my_strcat("", prompt);
        } else {
            my_printf("$> "); return 0;
        }
    }
    if (getcwd(prompt, sizeof(prompt)) != NULL)
        shell->temp_oldpwd = my_strcat("", prompt);
    change_oldpwd(shell);
    if (my_getenv(shell->env, "PWD") == NULL
        || getcwd(prompt, sizeof(prompt)) == NULL)
        return 84;
    for (; shell->env[i]; i++) {
        if (my_strncmp(shell->env[i], "PWD", 3) == 0) {
            key = my_strcat(key, prompt); shell->env[i] = my_strdup(key);
        }
    } return 0;
}
