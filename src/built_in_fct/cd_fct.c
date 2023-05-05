/*
** EPITECH PROJECT, 2022
** PROJECTS
** File description:
** cd_fct.c
*/
#include "42sh.h"

int cd_fct(shell_t *shell, char *filepath, int number_av)
{
    struct stat fstat; stat(filepath, &fstat);
    if (number_av > 1) {
my_eprintf("cd: Too many arguments.\n"); shell->temp_exit_code = 1; return 84;
    }
    if (stat(filepath, &fstat) == -1) {
        my_eprintf("%s: No such file or directory.\n",filepath);
        shell->temp_exit_code = 1; return 84;
    }
    if (!S_ISDIR(fstat.st_mode)) {
        my_eprintf("%s: Not a directory.\n", filepath);
        shell->temp_exit_code = 1; return 84;
    }
    if (access(filepath, X_OK) == -1) {
        my_eprintf("%s: Permission denied.\n", filepath);
        shell->temp_exit_code = 1; return 84;
    }
    if (chdir(filepath) == -1) {
        perror("cd"); shell->temp_exit_code = 1; return 84;
    } shell->oldpwd = shell->temp_oldpwd; shell->wasItCd = true;
    return 0;
}

int cd_no_av_fct(shell_t *shell, int number_av)
{
    char *path = my_getenv(shell->env, "HOME");
    if (number_av > 1) {
my_eprintf("cd: Too many arguments.\n"); shell->temp_exit_code = 1; return 84;
    } if (path == NULL && number_av == 0) {
my_eprintf("cd: No home directory.\n"); shell->temp_exit_code = 1; return 84;
    } if (path == NULL && number_av == 1) {
my_eprintf("No $home variable set.\n"); shell->temp_exit_code = 1; return 84;
    } struct stat fstat; stat(path, &fstat);
    if (stat(path, &fstat) == -1) {
        my_eprintf("cd: Can't change to home directory.\n",path);
        shell->temp_exit_code = 1; return 84;
    } if (!S_ISDIR(fstat.st_mode)) {
        my_eprintf("cd: Can't change to home directory.\n",path);
        shell->temp_exit_code = 1; return 84;
    } if (access(path, X_OK) == -1) {
        my_eprintf("cd: Can't change to home directory.\n",path);
        shell->temp_exit_code = 1; return 84;
    } if (chdir(path) == -1) {
        perror("cd"); shell->temp_exit_code = 1; return 84;
    } shell->oldpwd = shell->temp_oldpwd; shell->wasItCd = true; return 0;
}

int cd_dash_fct(int number_av, shell_t *shell)
{
    if (shell->wasItCd == false) {
        my_eprintf(": No such file or directory.\n");
        shell->temp_exit_code = 1;
        return 84;
    }
    if (number_av > 1) {
        my_eprintf("Usage: cd [-plvn][-|<dir>].\n");
        shell->temp_exit_code = 1;
        return 84;
    }
    char *str = my_getenv(shell->env, "OLDPWD");
    if (str == NULL || str[0] == '\0') {
        if (exec_cd_dash(shell, shell->oldpwd) != 84)
            shell->oldpwd = shell->temp_oldpwd;
        return 0;
    }
    if (exec_cd_dash(shell, str) != 84)
        shell->oldpwd = shell->temp_oldpwd;
    return 0;
}

int exec_cd_dash(shell_t *shell, char *oldpwd)
{
    if (access(oldpwd, X_OK) == -1) {
        my_eprintf("%s: Permission denied.\n", oldpwd);
        shell->temp_exit_code = 1;
        return 84;
    }
    if (chdir(oldpwd) == -1) {
        perror("cd");
        shell->temp_exit_code = 1;
        return 84;
    }
    return 0;
}
