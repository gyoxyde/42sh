/*
** EPITECH PROJECT, 2022
** minishell_2
** File description:
** redirection.c
*/
#include "42sh.h"

int my_right_redirection(shell_t *shell, char ***array, int *fd)
{
    bool fix_array = false; shell->fd = dup(STDOUT_FILENO);
    if (shell->redirect_str == NULL) {
        my_eprintf("Missing name for redirect.\n");
        shell->temp_exit_code = 1; return 84;
    } (*fd) = open(shell->redirect_str, O_WRONLY | O_TRUNC | O_CREAT, 0644);
    if ((*fd) < 0) {
        my_eprintf("%s: Permission denied.\n", shell->redirect_str);
        shell->temp_exit_code = 1 ;return 84;
    } for (int i = 0; (*array)[i] != NULL; i++) {
        if (my_strcmp((*array)[i], ">") == 0)
            fix_array = true;
        if (fix_array == true && (*array)[i + 1] != NULL)
            (*array)[i] = (*array)[i + 2];
    }
    if ((*array)[0] == NULL) {
        my_eprintf("Invalid null command.\n");
        shell->temp_exit_code = 1 ;return 84;
    } if (dup2((*fd), 1) < 0) {
        perror("dup2"); shell->temp_exit_code = 1; return 84;
    } return 0;
}

int my_doubleright_redirection(shell_t *shell, char ***array, int *fd)
{
    bool fix_array = false; shell->fd = dup(STDOUT_FILENO);
    if (shell->redirect_str == NULL) {
        my_eprintf("Missing name for redirect.\n");
        shell->temp_exit_code = 1; return 84;
    } (*fd) = open(shell->redirect_str, O_WRONLY | O_CREAT | O_APPEND,
    0644);
    if ((*fd) < 0) {
        my_eprintf("%s: Permission denied.\n", shell->redirect_str);
        shell->temp_exit_code = 1; return 84;
    } for (int i = 0; (*array)[i] != NULL; i++) {
        if (my_strcmp((*array)[i], ">>") == 0) {
            fix_array = true;
        } if (fix_array == true && (*array)[i + 1] != NULL)
            (*array)[i] = (*array)[i + 2];
    } if ((*array)[0] == NULL) {
        my_eprintf("Invalid null command.\n");
        shell->temp_exit_code = 1; return 84;
    } if (dup2((*fd), 1) < 0) {
        perror("dup2"); shell->temp_exit_code = 1; return 84;
    } return 0;
}

int my_left_redirection(shell_t *shell, char ***array, int *fd)
{
    bool fix_array = false; shell->fd2 = dup(STDIN_FILENO);
    if (shell->redirect_lstr == NULL) {
        my_eprintf("Missing name for redirect.\n");
        shell->temp_exit_code = 1; return 84;
    } if (access(shell->redirect_lstr, F_OK) == - 1) {
        my_eprintf("%s: No such file or directory.\n", shell->redirect_lstr);
        shell->temp_exit_code = 1 ; return 84;
    } (*fd) = open(shell->redirect_lstr, O_RDONLY);
    if ((*fd) < 0) {
        my_eprintf("%s: Permission denied.\n", shell->redirect_lstr);
        shell->temp_exit_code = 1 ;return 84;
    } for (int i = 0; (*array)[i] != NULL; i++) {
        if (my_strcmp((*array)[i], "<") == 0) fix_array = true;
if (fix_array == true && (*array)[i + 1] != NULL) (*array)[i] = (*array)[i + 2];
    } if ((*array)[0] == NULL) {
    my_eprintf("Invalid null command.\n"); shell->temp_exit_code = 1 ;return 84;
    } if (dup2((*fd), 0) < 0) {
        perror("dup2"); shell->temp_exit_code = 1; return 84;
    } return 0;
}

int my_doubleleft_redirection(shell_t *shell, char ***array, int *fd)
{
    bool fix_array = false; shell->fd2 = dup(STDIN_FILENO);
    if (shell->redirect_lstr == NULL) {
        my_eprintf("Missing name for redirect.\n");
        shell->temp_exit_code = 1; return 84;
    } if (access(shell->redirect_lstr, F_OK) == - 1) {
        my_eprintf("%s: No such file or directory.\n", shell->redirect_lstr);
        shell->temp_exit_code = 1 ; return 84;
    } (*fd) = open(shell->redirect_lstr, O_RDONLY, 0644);
    if ((*fd) < 0) {
        my_eprintf("%s: Permission denied.\n", shell->redirect_lstr);
        shell->temp_exit_code = 1; return 84;
    } for (int i = 0; (*array)[i] != NULL; i++) {
        if (my_strcmp((*array)[i], "<<") == 0) fix_array = true;
if (fix_array == true && (*array)[i + 1] != NULL) (*array)[i] = (*array)[i + 2];
    } if ((*array)[0] == NULL) {
    my_eprintf("Invalid null command.\n"); shell->temp_exit_code = 1; return 84;
    } if (dup2((*fd), 0) < 0) {
        perror("dup2"); shell->temp_exit_code = 1; return 84;
    } return 0;
}

// int fork_for_left_redirection(shell_t *shell, char **array, int *fd,
// int *pipefd)
// {
//     int number_av = shell->number_av; int status; char *buf;
//     //shell->isLeftDupDone = true;
//     shell->pid = fork();
//     if (shell->pid == 0) {
//         if (my_left_redirection(shell, &array, fd, pipefd) == 84)
//             return 84;
//     my_printf("J'me rapproche encore");

//         shell_redirection(shell, array, number_av, pipefd);
//         my_printf(" un peu plus chaque jour.");
//     } else {
//         close(pipefd[0]);
//         if (shell->pid > 0) {
//             close(pipefd[1]);
//             if (access(shell->redirect_lstr, F_OK) == - 1) {
//         my_eprintf("%s: No such file or directory.\n", shell->redirect_lstr);
//                 shell->temp_exit_code = 1 ; return 84;
//             } (*fd) = open(shell->redirect_lstr, O_RDONLY, 0644);
//                 if ((*fd) < 0) {
//                 my_eprintf("%s: Permission denied.\n", shell->redirect_lstr);
//                     shell->temp_exit_code = 1 ; return 84;
//                 }
//     write(pipefd[1],"batman", 6);
//     write(1,"batman2", 7);
//         while (read(pipefd[1], &buf, 1) > 0) {
//             write(pipefd[1], &buf, 1);
//             //write(STDOUT_FILENO, "\n", 1);
//         }
//         close(pipefd[0]);
//             wait(&status);
//         }
//     }
//     return 0;
// }
// int my_left_redirection(shell_t *shell, char ***array, int *fd, int *pipefd)
// {
//     close(pipefd[0]);
//     bool fix_array = false;
//     if (shell->redirect_lstr == NULL) {
//         my_eprintf("Missing name for redirect.\n");
//         shell->temp_exit_code = 1; return 84;
//     } for (int i = 0; (*array)[i] != NULL; i++) {
//         if (my_strcmp((*array)[i], "<") == 0)
//             fix_array = true;
//         if (fix_array == true && (*array)[i + 1] != NULL)
//             (*array)[i] = (*array)[i + 2];
//     } if ((*array)[0] == NULL) {
//  my_eprintf("Invalid null command.\n"); shell->temp_exit_code = 1 ;return 84;
//     } if (pipe(pipefd) == -1) {
//         perror("pipe");
//         return 84;
//     }

//     if (dup2((*fd), STDIN_FILENO) < 0) {
//         perror("dup2"); shell->temp_exit_code = 1; return 84;
//     }
//     close(pipefd[1]);
//     return 0;
// }
