/*
** EPITECH PROJECT, 2022
** minishell_2
** File description:
** shell.c
*/
#include "minishell_2.h"

int shell_start(shell_t *shell)
{
    shell->oldpwd = NULL; shell->temp_oldpwd = NULL;
    char *str; shell->wasItCd = false;
    shell->temp_exit_code = 0; shell->exit_code = shell->temp_exit_code;
    signal_handler(); shell->str = NULL;
    while (1) {
        shell->exit_code = shell->temp_exit_code; shell->temp_exit_code = 0;
        shell->index_array = 0;
        prompt(shell);
        str = my_getstr(shell);
        str = clean_str(str); str = clean_separator(str);
        str = clean_double_and(str);
        str = clean_right_redi(str); str = clean_left_redi(str);
        str = clean_pipe(str);
        shell->str = my_strdup(str);
        if (my_strcmp(str, "") != 0) {
            shell->number_av = count_av(str);
            shell_loop(shell, str);
        }
    }
    return 0;
}

int shell_loop(shell_t *shell, char *str)
{
    shell->exit_code = shell->temp_exit_code; shell->temp_exit_code = 0;
    shell->isLeftDupDone = false; shell->isRightDupDone = false;
    shell->recurs_pipe = false; shell->hasBeenPiped = false;
    char **temp_array = my_str_to_word_array(str, ' ');
    bool recurs = fill_array(shell, temp_array);
    char **array = shell->array; int number_av = 0;
    for (; shell->array[number_av] != NULL; number_av++);
    number_av = number_av - 1;
    if (check_redirection(shell, array) == true) {
        get_avnb(shell, array, &number_av);
    }
    if (check_error_redirection(shell, array, &recurs) == true)
        return 84;
    if (parthing_for_redirections(shell, array, number_av) == 84)
        return 84;
    if (recurs == true)
        shell_loop(shell, str);
    return 0;
}

int parthing_for_redirections(shell_t *shell, char **array, int number_av)
{
    int fd = 0;
    if (isitleftredirection(array) == true) {
        if (my_left_redirection(shell, &array, &fd) == 84)
            return 84;
        shell->isLeftDupDone = true;
        shell_redirection(shell, array, number_av);
        return 0;
    }
    if (isitdoubleleftredirection(array) == true) {
        if (my_doubleleft_redirection(shell, &array, &fd) == 84)
            return 84;
        shell->isLeftDupDone = true;
        shell_redirection(shell, array, number_av);
        return 0;
    }
    if (shell->isLeftDupDone == true)
        return 1;
    else
        shell_redirection(shell, array, number_av);
    return 0;
}

void shell_redirection(shell_t *shell,
char **array, int number_av)
{
    int fd = 0;
    if (isitrightredirection(array) == true) {
        if (my_right_redirection(shell, &array, &fd) == 84)
            return;
        shell->isRightDupDone = true;
    } if (isitdoublerightredirection(array) == true) {
        if (my_doubleright_redirection(shell, &array, &fd) == 84)
            return;
        shell->isRightDupDone = true;
    }
    create_pipe(shell);
    shell_do_fct(shell, array, number_av);
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
    my_eprintf("%s: Command not found.\n", array[0]); shell->temp_exit_code = 1;
        } else
            execute_cmd(array, shell);
    }
    close_all_fd(shell, array, number_av);
}
