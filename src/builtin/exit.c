/*
** EPITECH PROJECT, 2023
** minishell1
** File description:
** exit
*/

#include "../../include/my.h"

int my_exit(char **args, var_t m)
{
    int return_value = m->return_value;
    if (args[0] == NULL || args[0][0] == '\0' || args[0][0] == ' '){
        my_free_all();
        my_printf("exit\n");
        exit(return_value);
    }
    if (my_tablen((void **)args) > 1 || !my_strisnum(args[0])){
        (!my_is_num(args[0][0]) || my_tablen((void **)args) > 1) ?
        my_error("exit: Expression Syntax.\n") :
        my_error("exit: Badly formed number.\n");
        return 1;
    }
    if (my_strisnum(args[0])){
        return_value = get_nbr(args[0]);
        my_free_all();
        my_printf("exit\n");
        exit(return_value);
    }
    return 1;
}
