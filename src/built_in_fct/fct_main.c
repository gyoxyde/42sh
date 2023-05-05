/*
** EPITECH PROJECT, 2022
** PROJECTS
** File description:
** built_in_main.c
*/
#include "shell.h"

void built_in_function(char **array, shell_t *shell, int number_av)
{
    int wasIt_Built_in_fct = check_built_in_fct(array[0], array, number_av);
    if (wasIt_Built_in_fct != false) {
        if (wasIt_Built_in_fct == 1) cd_fct(shell, array[1], number_av);
        if (wasIt_Built_in_fct == 2) setenv_fct(shell, array, number_av);
        if (wasIt_Built_in_fct == 3) unsetenv_fct(shell, array, number_av);
        if (wasIt_Built_in_fct == 4) print_env(shell->env);
        if (wasIt_Built_in_fct == 5) exit_fct(number_av, shell, array);
        if (wasIt_Built_in_fct == 6) cd_no_av_fct(shell, number_av);
        if (wasIt_Built_in_fct == 7) cd_dash_fct(number_av, shell);
        if (wasIt_Built_in_fct == 8) fct_curr_dir(array, shell);
        if (wasIt_Built_in_fct == 9) fct_curr_dir(array, shell);
        if (wasIt_Built_in_fct == 10) cd_no_av_fct(shell, number_av);
    }
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
        if (my_strcmp(str, "cd") == 0
        && my_strcmp(array[1], "-") == 0) return 7;
        if (my_strcmp(str, "cd") == 0
        && my_strcmp(array[1], "~") == 0) return 10;
        if (my_strcmp(str, "cd") == 0) return 1;
        if (my_strcmp(str, "setenv") == 0) return 2;
        if (my_strcmp(str, "unsetenv") == 0) return 3;
        if (my_strncmp(str, "./", 2) == 0) return 8;
    } else {
        if (my_strcmp(str, "env") == 0) return 4;
        if (my_strcmp(str, "setenv") == 0) return 4;
        if (my_strcmp(str, "cd") == 0) return 6;
    }
    if (my_strcmp(str, "exit") == 0) return 5;
    if (my_strncmp(str, "./", 2) == 0) return 8;
    if (check_curr_dir(str) == 1) return 9;
    return 0;
}

void print_env(char **env)
{
    for (int i = 0; env[i] != NULL; i++)
        my_printf("%s\n", env[i]);
}
