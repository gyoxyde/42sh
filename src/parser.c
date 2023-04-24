/*
** EPITECH PROJECT, 2023
** minishell2
** File description:
** parser
*/

#include "../include/my.h"

char **clean_word_array(char *str, char c)
{
    char **commands_temp = to_word_array(str, c);
    char **commands = malloc(sizeof(char *) *
        (my_tablen((void *)commands_temp) + 1));
    int j = 0;

    for (int i = 0; commands_temp[i]; i++){
        commands_temp[i] = my_cleanstr(commands_temp[i]);
        if (commands_temp[i][0] != '\0')
            commands[j++] = my_strdup(commands_temp[i]);
    }
    commands[j] = NULL;
    for (int i = 0; commands[i]; i++)
        commands[i] = spaces_commands(commands[i]);
    return commands;
}

static int check_if_exit(char *str, var_t m)
{
    char **args;

    args = to_word_array(str, ' ');
    if (my_strcmp(args[0], "exit") != 1){
        my_error(args[0]);
        my_error(": commands not found.\n");
        return 1;
    }
    args++;
    if (args[0] == NULL || args[0][0] == '\0' || args[0][0] == ' ')
        return 1;
    if (my_tablen((void **)args) > 1 || !my_strisnum(args[0])){
        (!my_is_num(args[0][0]) || my_tablen((void **)args) > 1) ?
        my_error("exit: Expression Syntax.\n") :
        my_error("exit: Badly formed number.\n");
        return 0;
    }
    if (my_strisnum(args[0]))
        m->return_value = get_nbr(args[0]);
    return 1;
}

int parse_command(char *str, var_t m)
{
    char **commands;
    int exit_state = false;

    str[my_strlen(str) - 1] = '\0';
    commands = clean_word_array(str, ';');
    for (int i = 0; commands[i]; i++){
        if (my_strncmp(commands[i], "exit", 4) == 0){
            exit_state = (check_if_exit(commands[i], m) == 1) ? true : false;
            continue;
        }
        m->return_value = execute_command(commands[i], m);
    }
    if (exit_state){
        my_free_all();
        my_printf("exit\n");
        exit(m->return_value);
    }
    return m->return_value;
}
