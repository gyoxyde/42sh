/*
** EPITECH PROJECT, 2022
** minishell_2
** File description:
** shell.c
*/
#include "shell.h"

int shell_start(shell_t *shell)
{
    init_all(shell);
    while (1) {
        shell->exit_code = shell->temp_exit_code;
        shell->temp_exit_code = 0;
        shell->index_array = 0;
        prompt(shell);
        get_cleaned_str(shell);
        if (my_strcmp(shell->str, "") != 0) {
            shell->number_av = count_av(shell->str);
            char **temp_array = def_temp_array(shell);
            shell_loop(shell, temp_array);
        }
    }
    return 0;
}

void shell_loop(shell_t *shell, char **temp_array)
{
    bool recurs = fill_array(shell, temp_array);
    char **array = shell->array;
    int number_av = 0;
    init_loop(shell);
    if (check_globbings_env(shell, array) == 84) return;
    if (check_error_recursive(shell, temp_array) == true) return;
    for (; shell->array[number_av + 1] != NULL; number_av++);
    if (check_redirection(shell, array))
        get_avnb(shell, array, &number_av);
    if (check_error_redirection(shell, array, &recurs)) return;
    if (parthing_for_redirections(shell, array, number_av) == 84) return;
    if (close_right_fd(shell) == 84) return;
    if (recurs)
        shell_loop(shell, temp_array);
}

int parthing_for_redirections(shell_t *shell, char **array, int number_av)
{
    int fd = 0;

    if (isitleftredirection(array)) {
        if (my_left_redirection(shell, &array, &fd) == 84)
            return 84;
        return 0;
    }
    if (isitdoubleleftredirection(array)) {
        if (my_doubleleft_redirection(shell, &array) == 84)
            return 84;
        return 0;
    }
    if (shell->isLeftDupDone)
        return 1;
    return shell_redirection(shell, array, number_av);
}

int shell_redirection(shell_t *shell, char **array, int number_av)
{
    int fd = 0;

    if (isitrightredirection(array)) {
        if (my_right_redirection(shell, &array, &fd) == 84)
            return 0;
        shell->isRightDupDone = true;
    } if (isitdoublerightredirection(array)) {
        if (my_doubleright_redirection(shell, &array, &fd) == 84)
            return 0;
        shell->isRightDupDone = true;
    }
    create_pipe(shell);
    shell_do_fct(shell, array, number_av);
    return 0;
}

void shell_do_fct(shell_t *shell, char **array, int number_av)
{
    if (pipe_loop(shell->array, shell) == -1) {
        close_all_fd(shell, array, number_av);
        return;
    }
    array = shell->array_pipe;
    number_av = 0;
    for (; array[number_av] != NULL; number_av++);
    number_av = number_av - 1;
    get_correct_path_fct(array, shell);
    built_in_function(array, shell, number_av);
    if (check_built_in_fct(array[0], array, number_av) == 0) {
        if (shell->index_path_found == -1) {
            my_eprintf("%s: Command not found.\n", array[0]);
            shell->temp_exit_code = 1;
        } else
            execute_cmd(array, shell);
    }
}
