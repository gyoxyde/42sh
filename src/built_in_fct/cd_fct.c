/*
** EPITECH PROJECT, 2022
** PROJECTS
** File description:
** cd_fct.c
*/
#include "shell.h"

int cd_error_message(int type, shell_t *shell, char *str)
{
    if (type == TOO_MANY) my_eprintf("cd: Too many arguments.\n");
    if (type == NO_FILE) my_eprintf("%s: No such file or directory.\n", str);
    if (type == NOT_DIR) my_eprintf("%s: Not a directory.\n", str);
    if (type == PERM_DENIED) my_eprintf("%s: Permission denied.\n", str);
    if (type == NO_HOME) my_eprintf("cd: No home directory.\n");
    if (type == NO_HOME_VAR) my_eprintf("No $home variable set.\n");
    if (type == CHDIR) perror("cd");
    if (type == NO_HOME2) my_eprintf("cd: Can't change to home directory.\n");

    shell->temp_exit_code = 1;
    return 84;
}

int cd_fct(shell_t *shell, char *filepath, int number_av)
{
    struct stat fstat;
    stat(filepath, &fstat);

    if (number_av > 1)
        return cd_error_message(TOO_MANY, shell, NULL);
    if (stat(filepath, &fstat) == -1)
        return cd_error_message(NO_FILE, shell, filepath);
    if (!S_ISDIR(fstat.st_mode))
        return cd_error_message(NOT_DIR, shell, filepath);
    if (access(filepath, X_OK) == -1)
        return cd_error_message(PERM_DENIED, shell, filepath);
    if (chdir(filepath) == -1)
        return cd_error_message(CHDIR, shell, NULL);

    shell->oldpwd = shell->temp_oldpwd;
    shell->wasItCd = true;
    return 0;
}

int cd_no_av_fct(shell_t *shell, int number_av)
{
    char *path = my_getenv(shell->env, "HOME");
    struct stat fstat;

    if (number_av > 1)
        return cd_error_message(TOO_MANY, shell, NULL);
    if (path == NULL && number_av == 0)
        return cd_error_message(NO_HOME, shell, NULL);
    if (path == NULL && number_av == 1)
        return cd_error_message(NO_HOME_VAR, shell, NULL);
    if (stat(path, &fstat) == -1)
        return cd_error_message(NO_HOME2, shell, NULL);
    if (!S_ISDIR(fstat.st_mode))
        return cd_error_message(NO_HOME2, shell, path);
    if (access(path, X_OK) == -1)
        return cd_error_message(PERM_DENIED, shell, path);
    if (chdir(path) == -1)
        return cd_error_message(CHDIR, shell, NULL);
    shell->oldpwd = shell->temp_oldpwd;
    shell->wasItCd = true;
    return 0;
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
