/*
** EPITECH PROJECT, 2022
** noPushMinishell
** File description:
** main.c
*/
#include "shell.h"

int main(int ac, char **const av, char** env)
{
    printf("\033[0;30m");
    (void)av;
    shell_t *shell = malloc(sizeof(shell_t));
    if (shell == NULL)
        exit(84);
    shell->p = malloc(sizeof(pipes_t));
    if (ac != 1)
        exit(84);
    shell->env = env;
    init_local(shell);
    shell_start(shell);
    printf("\033[0m");
    return 0;
}
