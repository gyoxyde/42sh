/*
** EPITECH PROJECT, 2022
** minishell_2
** File description:
** shell.c
*/
#include "42sh.h"

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
            shell_loop(shell);
        }
    }
    return 0;
}

int shell_loop(shell_t *shell)
{
    char **temp_array = my_str_to_word_array(shell->str, ' ');
    bool recurs = fill_array(shell, temp_array);
    char **array = shell->array;
    int number_av = 0;

    init_loop(shell);
    for (; shell->array[number_av] != NULL; number_av++);
    number_av = number_av - 1;
    if (check_redirection(shell, array))
        get_avnb(shell, array, &number_av);
    if (check_error_redirection(shell, array, &recurs))
        return 84;
    if (parthing_for_redirections(shell, array, number_av) == 84)
        return 84;
    if (recurs)
        shell_loop(shell);
    return 0;
}

int parthing_for_redirections(shell_t *shell, char **array, int number_av)
{
    int fd = 0;

    if (isitleftredirection(array)) {
        if (my_left_redirection(shell, &array, &fd) == 84)
            return 84;
        shell->isLeftDupDone = true;
        return shell_redirection(shell, array, number_av);
    }
    if (isitdoubleleftredirection(array)) {
        if (my_doubleleft_redirection(shell, &array, &fd) == 84)
            return 84;
        shell->isLeftDupDone = true;
        return shell_redirection(shell, array, number_av);
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
    pipe_loop(shell->array, shell);
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
    close_all_fd(shell, array, number_av);
}
