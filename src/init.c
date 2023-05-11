/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** init
*/

#include "shell.h"

void init_all(shell_t *shell)
{
    shell->oldpwd = NULL;
    shell->temp_oldpwd = NULL;
    shell->wasItCd = false;
    shell->temp_exit_code = 0;
    shell->exit_code = shell->temp_exit_code;
    shell->str = NULL;
    shell->i->history_index = 0;
    shell->i->history_length = 0;
    shell->i->history = malloc(sizeof(char *) * 100);
    shell->i->history[0] = NULL;
    signal_handler();
}

void init_loop(shell_t *shell)
{
    shell->isLeftDupDone = false;
    shell->isRightDupDone = false;
    shell->recurs_pipe = false;
    shell->hasBeenPiped = false;
    shell->islocal = false;
}

static void init_local_bis(shell_t *shell, int *i)
{
    if (getlogin()) my_asprintf(&shell->local[(*i)++], "user=%s", getlogin());
    char *home = my_getenv(shell->env, "HOME");
    if (home) my_asprintf(&shell->local[(*i)++], "home=%s", home);
    my_asprintf(&shell->local[(*i)++], "shlvl=1");
    my_asprintf(&shell->local[(*i)++], "version=42sh");
    char *oldpwd = my_getenv(shell->env, "OLDPWD");
    if
        (oldpwd) my_asprintf(&shell->local[(*i)++], "owd=%s", oldpwd);
    else
        my_asprintf(&shell->local[(*i)++], "owd=");
    char *term = my_getenv(shell->env, "TERM");
    if (term) my_asprintf(&shell->local[(*i)++], "term=%s", term);
    char *cwd = getcwd(NULL, 0);
    if (cwd) my_asprintf(&shell->local[(*i)++], "shell=%s", cwd);
}

void init_local(shell_t *shell)
{
    int i = 0;
    shell->local = malloc(sizeof(char *) * 128);
    my_asprintf(&shell->local[i++], "_=");
    char *path = my_getenv(shell->env, "PATH");
    if (path)
        my_asprintf(&shell->local[i++], "path=(%s)", path);
    else
        my_asprintf(&shell->local[i++], "path=(/usr/bin:/bin)");
    char *cwd = getcwd(NULL, 0);
    if (cwd) my_asprintf(&shell->local[i++], "cwd=%s", cwd);
    init_local_bis(shell, &i);
    shell->local[i] = NULL;
}
