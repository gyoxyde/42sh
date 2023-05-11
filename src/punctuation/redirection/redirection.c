/*
** EPITECH PROJECT, 2022
** minishell_2
** File description:
** redirection.c
*/
#include "shell.h"

int my_right_redirection(shell_t *shell, char ***array, int *fd)
{
    bool fix_array = false;
    shell->fd = dup(STDOUT_FILENO);
    if (shell->redirect_str == NULL)
        return redi_error_message(NO_NAME, shell, shell->redirect_str);
    if (check_pipe_redirection(shell, (*array), ">", RIGHT_REDI) == 84)
        return 84;
    (*fd) = open(shell->redirect_str, O_WRONLY | O_TRUNC | O_CREAT, 0644);
    if ((*fd) < 0)
        return redi_error_message(PERM_DENIED, shell, shell->redirect_str);
    for (int i = 0; (*array)[i] != NULL; i++) {
        if (my_strcmp((*array)[i], ">") == 0)
            fix_array = true;
        if (fix_array == true && (*array)[i + 1] != NULL)
            (*array)[i] = (*array)[i + 2];
    }
    if ((*array)[0] == NULL)
        return redi_error_message(INVALID_CMD, shell, shell->redirect_str);
    if (dup2((*fd), 1) < 0)
        return redi_error_message(NO_DUP2, shell, shell->redirect_str);
    return 0;
}

int my_doubleright_redirection(shell_t *shell, char ***array, int *fd)
{
    bool fix_array = false;
    shell->fd = dup(STDOUT_FILENO);
    if (shell->redirect_str == NULL)
        return redi_error_message(NO_NAME, shell, shell->redirect_str);
    if (check_pipe_redirection(shell, (*array), ">>", RIGHT_REDI) == 84)
        return 84;
    (*fd) = open(shell->redirect_str, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if ((*fd) < 0)
        return redi_error_message(PERM_DENIED, shell, shell->redirect_str);
    for (int i = 0; (*array)[i] != NULL; i++) {
        if (my_strcmp((*array)[i], ">>") == 0)
            fix_array = true;
        if (fix_array == true && (*array)[i + 1] != NULL)
            (*array)[i] = (*array)[i + 2];
    }
    if ((*array)[0] == NULL)
        return redi_error_message(INVALID_CMD, shell, shell->redirect_str);
    if (dup2((*fd), 1) < 0)
        return redi_error_message(NO_DUP2, shell, shell->redirect_str);
    return 0;
}

int my_left_redirection(shell_t *shell, char ***array, int *fd)
{
    bool fix_array = false;
    shell->fd2 = dup(STDIN_FILENO);
    if (shell->redirect_lstr == NULL)
        return redi_error_message(NO_NAME, shell, shell->redirect_lstr);
    if (access(shell->redirect_lstr, F_OK) == -1)
        return redi_error_message(NO_FILE, shell, shell->redirect_lstr);
    if (check_pipe_redirection(shell, (*array), "<", LEFT_REDI) == 84)
        return 84;
    (*fd) = open(shell->redirect_lstr, O_RDONLY);
    if ((*fd) < 0)
        return redi_error_message(PERM_DENIED, shell, shell->redirect_lstr);
    for (int i = 0; (*array)[i] != NULL; i++) {
        if (my_strcmp((*array)[i], "<") == 0)
            fix_array = true;
        if (fix_array == true && (*array)[i + 1] != NULL)
            (*array)[i] = (*array)[i + 2];
    }
    if ((*array)[0] == NULL)
        return redi_error_message(INVALID_CMD, shell, shell->redirect_lstr);
    return dup_redirection((*array), shell, (*fd), 0);
}

char *get_heredoc(char *end_of_file, shell_t *shell)
{
    size_t size = 0; ssize_t read;
    char *co = NULL; char *str = "";
    if (isatty(0))
        my_printf("? ");
    read = getline(&co, &size, stdin);
    while (read != -1) {
        co[my_strlen(co) - 1] = '\0';
        if (my_strcmp(co, end_of_file) == 0)
            break;
        if (my_strcmp(co, "") != 0) {
            str = my_strcat(str, co);
            str = my_strcat(str, "\n");
        } if (isatty(0))
            my_printf("? ");
        free(co);
        co = NULL;
        read = getline(&co, &size, stdin);
    } if (read == -1)
        exit(shell->exit_code);
    return str;
}

int my_doubleleft_redirection(shell_t *shell, char ***array)
{
    bool fix_array = false;
    shell->fd2 = dup(STDIN_FILENO);
    char *file = NULL;
    int pipefd[2];

    if (shell->redirect_lstr == NULL)
        return redi_error_message(NO_NAME, shell, shell->redirect_lstr);
    if (check_pipe_redirection(shell, (*array), "<<", LEFT_REDI) == 84)
        return 84;
    for (int i = 0; (*array)[i] != NULL; i++) {
        if (my_strcmp((*array)[i], "<<") == 0)
            fix_array = true;
        if (fix_array == true && (*array)[i + 1] != NULL)
            (*array)[i] = (*array)[i + 2];
    }
    if ((*array)[0] == NULL)
        return redi_error_message(INVALID_CMD, shell, shell->redirect_lstr);
    if (write_double_left_pipe(shell, pipefd, file) == 84)
        return 84;
    return dup_redirection((*array), shell, pipefd[0], 0);
}
