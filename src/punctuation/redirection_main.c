/*
** EPITECH PROJECT, 2022
** minishell_2
** File description:
** redirection_main.c
*/
#include "42sh.h"

bool check_error_redirection(shell_t *shell, char **array, bool *recurs)
{
    int simple_redR = 0; int double_redR = 0; bool missingName = false;
    shell->index_simpleR = -1; shell->index_doubleR = -1; int nb_right = 0;
    int simple_redL = 0; int double_redL = 0; shell->index_redi = 0;
    shell->index_simpleL = -1; shell->index_doubleL = -1; int nb_left = 0;
    for (; array[shell->index_redi] != NULL; shell->index_redi++) {
if (count_redirections(array, shell->index_redi, &nb_right, &nb_left) == 84) {
            missingName = true;
    }
    add_redright(shell, array, &simple_redR, &double_redR);
    add_redleft(shell, array, &simple_redL, &double_redL);
}
if (((shell->index_simpleR != - 1 && array[shell->index_simpleR + 1] == NULL)
|| (shell->index_doubleR != -1 && array[shell->index_doubleR + 1] == NULL))
|| missingName == true) {
        my_eprintf("Missing name for redirect.\n");
        shell->temp_exit_code = 1; (*recurs) = false; return true;
    } if (nb_left > 2 || nb_right > 2 || simple_redR > 1 || simple_redL > 1) {
        my_eprintf("Ambiguous output redirect.\n");
        shell->temp_exit_code = 1; (*recurs) = false; return true;
    } return false;
}

int count_redirections(char **array, int i, int *nb_right, int *nb_left)
{
    bool checkForNullL = false; bool checkForNullR = false;
    for (int j = 0; array[i][j] != '\0'; j++) {
        if (array[i][j] == '>') {
            (*nb_right)++; checkForNullR = true;
        }
        if (array[i][j] == '<') {
            (*nb_left)++; checkForNullL = true;
        }
        if (check_second_redi(array, i, j) == 84)
            return 84;
    }
    if ((*nb_right) >= 3 || (*nb_left) >= 3)
        return 84;
    if (checkForNullL == true || checkForNullR == true)
        if (array[i + 1] == NULL)
            return 84;
    return 0;
}

int check_second_redi(char **array, int i, int j)
{
    if (array[i + 1] == NULL)
        return 0;
    if ((array[i][j] == '<' && my_strcmp(array[i + 1], ">") == 0)
    || (array[i][j] == '<' && my_strcmp(array[i + 1], ">>") == 0))
        return 84;
    if ((array[i][j] == '>' && my_strcmp(array[i + 1], "<") == 0)
    || (array[i][j] == '>' && my_strcmp(array[i + 1], "<<") == 0))
        return 84;
    if ((array[i][j] == '<' && array[i][j + 1] == '<'
    && my_strcmp(array[i + 1], ">") == 0)
    || (array[i][j] == '<' && array[i][j + 1] == '<'
    && my_strcmp(array[i + 1], ">>") == 0))
        return 84;
    if ((array[i][j] == '>' && array[i][j + 1] == '>'
    && my_strcmp(array[i + 1], "<") == 0)
    || (array[i][j] == '>' && array[i][j + 1] == '>'
    && my_strcmp(array[i + 1], "<<") == 0))
        return 84;
    return 0;
}

void add_redright(shell_t *shell, char **array,
int *simple_redR, int *double_redR)
{
    if (my_strcmp(array[shell->index_redi], ">") == 0) {
            (*simple_redR)++; shell->index_simpleR = shell->index_redi;
        } if (my_strcmp(array[shell->index_redi], ">>") == 0) {
            (*double_redR)++; shell->index_doubleR = shell->index_redi;
        }
}

void add_redleft(shell_t *shell, char **array,
int *simple_redL, int *double_redL)
{
    if (my_strcmp(array[shell->index_redi], "<") == 0) {
            (*simple_redL)++; shell->index_simpleL = shell->index_redi;
        } if (my_strcmp(array[shell->index_redi], "<<") == 0) {
            (*double_redL)++; shell->index_doubleL = shell->index_redi;
        }
}
