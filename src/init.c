/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** init
*/

#include "42sh.h"

void init_all(shell_t *shell)
{
    shell->oldpwd = NULL;
    shell->temp_oldpwd = NULL;
    shell->wasItCd = false;
    shell->temp_exit_code = 0;
    shell->exit_code = shell->temp_exit_code;
    shell->str = NULL;
    signal_handler();
}

void init_loop(shell_t *shell)
{
    shell->exit_code = shell->temp_exit_code;
    shell->temp_exit_code = 0;
    shell->isLeftDupDone = false;
    shell->isRightDupDone = false;
    shell->recurs_pipe = false;
    shell->hasBeenPiped = false;
}
