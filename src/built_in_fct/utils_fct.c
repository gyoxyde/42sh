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
    char *path_value;
    if (shell->islocal) {
        path_value = my_getlocal(shell, "path");
        path_value++;
        path_value[my_strlen(path_value) - 1] = '\0';
    } else
        path_value = my_getenv(shell->env, "PATH");
    char **path_arr = my_str_to_word_array(path_value, ':');
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

void exec_parent_process(shell_t *shell, char **array)
{
    int number_av = 0;

    for (; array[number_av]; number_av++);
    number_av--;
    pipe_parent(shell);
    close_all_fd(shell, array, number_av);
}
