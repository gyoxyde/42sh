/*
** EPITECH PROJECT, 2022
** PROJECTS
** File description:
** path_handler.c
*/
#include "shell.h"

int get_correct_path_local(char **array, shell_t *shell)
{
    int i = 0;
    shell->index_path_found = -1;
    char *path = my_getlocal(shell, "path");
    char **path_array;

    if (path == NULL)
        return -1;
    path++;
    for (int i = 0; path[i]; i++)
        if (path[i] == ')')
            path[i] = '\0';
    path_array = my_str_to_word_array(path, ':');
    for (; path_array[i]; i++) {
        if (check_if_fct_is_here(path_array, array, i) == 0) {
            shell->islocal = true;
            shell->index_path_found = i;
            return shell->index_path_found;
        }
    }
    return -1;
}

int check_if_fct_is_here(char **path_array, char **array, int index)
{
    struct stat fstat;
    char *temp_str = my_strcat(path_array[index], "/");
    char *path = my_strcat(temp_str, array[0]);
    if (stat(path, &fstat) == -1) {
        return 84;
    }
    if (access(path, X_OK) == 0) {
        if (S_ISREG(fstat.st_mode))
            return 0;
    }
    return -1;
}

int get_correct_path_fct(char **array, shell_t *shell)
{
    int i = 0;
    shell->index_path_found = -1;
    char *path = my_getenv(shell->env, "PATH");
    char **path_array;
    if (path == NULL) {
        shell->islocal = true;
        return get_correct_path_local(array, shell);
    }
    path_array = my_str_to_word_array(path, ':');
    for (; path_array[i]; i++) {
        if (check_if_fct_is_here(path_array, array, i) == 0) {
            shell->index_path_found = i;
            return shell->index_path_found;
        }
    }
    if (shell->index_path_found != -1)
        return shell->index_path_found;
    shell->index_path_found = 0;
    return shell->index_path_found;
}
