/*
** EPITECH PROJECT, 2023
** minishell1
** File description:
** system_commands
*/

#include "../../include/my.h"
#include "../../include/sig_error.h"

int my_other(char **args, var_t m)
{
    pid_t pid = fork();
    int return_value = 0;
    errno = 0;

    if (pid == 0) {
        exit(my_execute(args, m));
    } else if (pid > 0) {
        waitpid(-1, &return_value, WUNTRACED);
        return error_message(return_value);
    } else {
        my_free_all();
        exit(my_error(my_strcat(strerror(errno), ".\n")));
    }
    return 2;
}

int error_message(int return_value)
{
    if (WEXITSTATUS(return_value) == 255)
        return 1;

    for (int i = 0; sig_list[i].return_value != 0; i++){
        if (WTERMSIG(return_value) == sig_list[i].signal){
            my_error(sig_list[i].error_message);
            (WCOREDUMP(return_value)) ?
            my_error(" (core dumped)") : 0;
            my_error("\n");
            return sig_list[i].return_value;
        }
    }
    return WEXITSTATUS(return_value);
}
