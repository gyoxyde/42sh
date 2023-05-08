/*
** EPITECH PROJECT, 2022
** upd42sh
** File description:
** utils_fct.c
*/

#include "shell.h"

int check_exec_cmd(char **array, shell_t *shell, char **path)
{
    if (check_path(shell, array) != 0)
        return 84;
    char **path_arr = my_str_to_word_array(my_getenv(shell->env, "PATH"), ':');
    char *temp_str = my_strcat(path_arr[shell->index_path_found], "/");
    (*path) = my_strcat(temp_str, array[0]);
    if (isitdir_exec_cmd(array, shell, (*path)) != 0)
        return 84;
    return 0;
}

void exec_child_process(shell_t *shell, char **array, char *path)
{
    pipe_child(shell);
    if (execve(path, array, shell->env) == -1) {
        check_errno(array);
        exit(84);
    }
}

void exec_parent_process(shell_t *shell, int status, int temp_status)
{
    pipe_parent(shell);
    wait(&status);
    temp_status = status;
    check_error_segfault(temp_status, shell);
}
