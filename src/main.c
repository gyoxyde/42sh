/*
** EPITECH PROJECT, 2023
** minishell1
** File description:
** main
*/

#include "../include/my.h"

static int (*execute[])(char **, var_t) = {
    &my_exit, &my_cd, &my_env, &my_setenv, &my_unsetenv,
    &my_redirection, &my_db_redirection, &my_input, &my_db_input, &my_other};


int loop(var_t m)
{
    size_t size = 0;
    ssize_t read;
    char *co = NULL;
    int return_value;

    read = getline(&co, &size, stdin);
    while (read != -1) {
        m->return_value = parse_command(co, m);
        if (isatty(0))
            my_printf("$> ");
        free(co);
        co = NULL;
        read = getline(&co, &size, stdin);
    }
    return_value = m->return_value;
    free(co);
    return return_value;
}

int main(int ac, __attribute__((unused)) char **av, char **env)
{
    var_t m = malloc(sizeof(my_var));
    int value;

    if (ac != 1){
        my_free_all();
        return my_error("No argument expected\n");
    }
    init_struct(m, env);
    if (isatty(0))
        my_printf("$> ");
    loop(m);
    if (isatty(0))
        my_printf("exit\n");
    value = m->return_value;
    my_free_all();
    return value;
}

int search_know_command(char **args, var_t m)
{
    char *commands[] = {"exit", "cd", "env", "setenv", "unsetenv",
        ">", ">>", "<", "<<", NULL};
    for (int i = 0, j = 5; args[i]; j++){
        if (!commands[j]){
            i++;
            j = 4;
            continue;
        }
        if (my_strcmp(args[i], commands[j]))
            return execute[j](args, m);
    }
    for (int i = 0; i < 5; i++){
        if (my_strcmp(args[0], commands[i]))
            return execute[i]((++args), m);
    }
    return execute[my_tablen((void **)commands)](args, m);
}

int execute_command(char *command, var_t m)
{
    char *clean_command = NULL;
    char **args = NULL;
    int pipes = 0;

    clean_command = my_cleanstr(command);
    if (clean_command[0] == '\0')
        return 0;
    for (int i = 0; clean_command[i]; i++)
        if (clean_command[i] == '|')
            pipes++;
    if (pipes == 0){
        args = to_word_array(clean_command, ' ');
        args = search_return_val(args, m);
        return search_know_command(args, m);
    }
    return create_pipe(clean_command, m);
}
