/*
** EPITECH PROJECT, 2022
** noPushMinishell
** File description:
** main.c
*/
#include "42sh.h"

int main(int ac, char **const av, char** env)
{
    (void)av;
    shell_t *shell = malloc(sizeof(shell_t));
    if (shell == NULL)
        exit(84);
    shell->p = malloc(sizeof(pipes_t));
    if (ac != 1)
        exit(84);
    shell->env = env;
    shell_start(shell);
    return 0;
}

/*
_ (old command)
path
cwd (pwd)
user
home
shlvl
version?
owd (old pwd)
xterm (term)
shell (pwd)
(dans l'ordre alphabetique)
(set a=z)
(5espaces entre var et val)
*/
