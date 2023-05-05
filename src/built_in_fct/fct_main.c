/*
** EPITECH PROJECT, 2022
** PROJECTS
** File description:
** built_in_main.c
*/
#include "shell.h"

void built_in_function(char **array, shell_t *shell, int number_av)
{
    int is_builtin = check_built_in_fct(array[0], array, number_av);
    if (is_builtin == NOT_BUILT_IN)
        return;
    if (is_builtin == CD) cd_fct(shell, array[1], number_av);
    if (is_builtin == SETENV) setenv_fct(shell, array, number_av);
    if (is_builtin == UNSETENV) unsetenv_fct(shell, array, number_av);
    if (is_builtin == ENV) print_env(shell->env);
    if (is_builtin == EXIT) exit_fct(number_av, shell, array);
    if (is_builtin == CD_NO_AV) cd_no_av_fct(shell, number_av);
    if (is_builtin == CD_DASH) cd_dash_fct(number_av, shell);
    if (is_builtin == EXECUTE) fct_curr_dir(array, shell);
    if (is_builtin == EXECUTE_CURR_DIR) fct_curr_dir(array, shell);
    if (is_builtin == CD_WAVE) cd_no_av_fct(shell, number_av);
}

int execute_cmd(char **array, shell_t *shell)
{
    if (check_path(shell, array) != 0) return 84;
char **path_array = my_str_to_word_array(my_getenv(shell->env, "PATH"), ':');
    char *temp_str = my_strcat(path_array[shell->index_path_found], "/");
    char *path = my_strcat(temp_str, array[0]); int temp_status;
    if (isitdir_exec_cmd(array, shell, path) != 0) return 84;
    int status; pid_t pid = fork();
    if (pid == 0) {
        pipe_child(shell);
        if (execve(path, array, shell->env) == -1) {
            my_eprintf("%s: Command not found.\n", array[0]); exit(84);
        }
    } else {
        if (pid > 0) {
            pipe_parent(shell); wait(&status); temp_status = status;
            check_error_segfault(temp_status, shell);
        } else {
        perror("fork"); exit(84);
        }
    }
    return 0;
}

int check_path(shell_t *shell, char **array)
{
    char *str = my_getenv(shell->env, "PATH");
    if (str[0] == '\0') {
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
    } else {
        if (!my_strcmp(str, "env")) return ENV;
        if (!my_strcmp(str, "setenv")) return ENV;
        if (!my_strcmp(str, "cd")) return CD_NO_AV;
    }
    if (!my_strcmp(str, "exit")) return EXIT;
    if (!my_strncmp(str, "./", 2)) return EXECUTE;
    if (check_curr_dir(str)) return EXECUTE_CURR_DIR;
    return NOT_BUILT_IN;
}

void print_env(char **env)
{
    for (int i = 0; env[i] != NULL; i++)
        my_printf("%s\n", env[i]);
}
