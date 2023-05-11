/*
** EPITECH PROJECT, 2022
** PROJECTS
** File description:
** built_in_main.c
*/
#include "shell.h"

int do_built_in(shell_t *shell, char **array, int number_av, int is_builtin)
{
    if (is_builtin == CD)               cd_fct(shell, array[1], number_av);
    if (is_builtin == SETENV)           setenv_fct(shell, array, number_av);
    if (is_builtin == UNSETENV)         unsetenv_fct(shell, array, number_av);
    if (is_builtin == ENV)              print_env(shell->env);
    if (is_builtin == EXIT)             exit_fct(number_av, shell, array);
    if (is_builtin == CD_NO_AV)         cd_no_av_fct(shell, number_av);
    if (is_builtin == CD_DASH)          cd_dash_fct(number_av, shell);
    if (is_builtin == EXECUTE)          fct_curr_dir(array, shell);
    if (is_builtin == EXECUTE_CURR_DIR) fct_curr_dir(array, shell);
    if (is_builtin == CD_WAVE)          cd_no_av_fct(shell, number_av);
    if (is_builtin == SET)              my_setlocal(shell, array);
    if (is_builtin == UNSET)            my_unset(shell, array);
    if (is_builtin == AL_NO_AV)         alias_no_av_fct(shell);
    if (is_builtin == AL)               alias_fct(shell);
    if (is_builtin == AL_ONE_AV)        alias_one_av(shell);
    if (is_builtin == UA)               unalias_function(shell);
    if (is_builtin == UA_NO_AV)     printf("unalias: Too few arguments.\n");
    if (is_builtin == EC)              echo_function(array);
    return 0;
}

void built_in_function(char **array, shell_t *shell, int number_av)
{
    int is_builtin = check_built_in_fct(array[0], array, number_av);
    if (is_builtin == NOT_BUILT_IN)
        return;
    if (shell->hasBeenPiped == false) {
        do_built_in(shell, array, number_av, is_builtin);
        return;
    }
    pid_t pid = fork();
    if (pid == 0) {
        pipe_child(shell);
        exit(do_built_in(shell, array, number_av, is_builtin));
    } else {
        if (pid > 0) {
            pipe_parent(shell);
            close_all_fd(shell, array, number_av);
        } else {
        perror("fork");
        exit(84);
        }
    }
}

int execute_cmd(char **array, shell_t *shell)
{
    char *path = NULL;
    pid_t pid;

    if (check_exec_cmd(array, shell, &path) == 84)
        return 84;
    pid = fork();
    if (pid == 0) {
        exec_child_process(shell, array, path);
    } else {
        if (pid > 0) {
            exec_parent_process(shell, array);
        } else {
            perror("fork");
            exit(84);
        }
    }
    return 0;
}

int check_path(shell_t *shell, char **array)
{
    char *path_value;
    if (shell->islocal) {
        path_value = my_getlocal(shell, "path");
        path_value++;
        path_value[my_strlen(path_value) - 1] = '\0';
    } else
        path_value = my_getenv(shell->env, "PATH");
    if (path_value[0] == '\0') {
        my_eprintf("%s: Command not found.\n", array[0]);
        shell->temp_exit_code = 1;
        return 84;
    }
    return 0;
}

int check_built_in_fct(char *str, char **array, int number_av)
{
    if (number_av != 0) {
        if (!my_strcmp(str, "cd") && !my_strcmp(array[1], "-")) return CD_DASH;
        if (!my_strcmp(str, "cd") && !my_strcmp(array[1], "~")) return CD_WAVE;
        if (!my_strcmp(str, "cd")) return CD;
        if (!my_strcmp(str, "setenv")) return SETENV;
        if (!my_strcmp(str, "unsetenv")) return UNSETENV;
        if (!my_strncmp(str, "./", 2)) return EXECUTE;
        if (check_which_alias(number_av, str) == 12) return AL;
        if (check_which_alias(number_av, str) == 13) return AL_ONE_AV;
        if (!my_strcmp(str, "unalias")) return UA;
        if (!my_strcmp(str, "echo")) return EC;
    } else {
        if (!my_strcmp(str, "env")) return ENV;
        if (!my_strcmp(str, "setenv")) return ENV;
        if (!my_strcmp(str, "cd")) return CD_NO_AV;
        if (my_strcmp(str, "alias") == 0) return AL_NO_AV;
        if (!my_strcmp(str, "unalias")) return UA_NO_AV;
    }
    return check_built_in_fct2(str);
}
