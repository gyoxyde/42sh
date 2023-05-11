/*
** EPITECH PROJECT, 2022
** PROJECTS
** File description:
** error_handling.c
*/
#include "shell.h"

void ctrl_c_handler(int signum)
{
    my_printf("\n");
    (void) signum;
    char prompt[PATH_MAX];
    if (isatty(0) == 1) {
        if (getcwd(prompt, sizeof(prompt)) != NULL)
            my_printf("[%s] ", prompt);
        else
            my_printf("$> ");
    }
}

void ctrl_z_handler(int signum)
{
    (void) signum;
}

void signal_handler(void)
{
    if (signal(SIGINT, &ctrl_c_handler) == SIG_ERR)
        exit(84);
    if (signal(SIGTSTP, &ctrl_z_handler) == SIG_ERR)
        exit(84);
}

void print_error(char *str)
{
    write(2, str, my_strlen(str));
}

int check_error_segfault(int status, shell_t *shell)
{
    if (status == 21504) shell->temp_exit_code = 1;
    if (status == 512) shell->temp_exit_code = 2;
    if (status != 21504 && status != 512) shell->temp_exit_code = status;
    if (WIFEXITED(status) == false) {
        shell->temp_exit_code = WTERMSIG(status);
        if (WTERMSIG(status) == SIGSEGV)
            shell->temp_exit_code = 139;
        if (WTERMSIG(status) == SIGABRT)
            shell->temp_exit_code = 134;
        if (WTERMSIG(status) == SIGFPE)
            shell->temp_exit_code = 136;
    if (my_strcmp(strsignal(WTERMSIG(status)), "Floating point exception") == 0)
            my_eprintf("Floating exception");
        else
            print_error(strsignal(WTERMSIG(status)));
        if (__WCOREDUMP(status) != 0)
            my_eprintf(" (core dumped)");
        my_eprintf("\n");
    }
    return 0;
}
