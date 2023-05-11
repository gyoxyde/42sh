/*
** EPITECH PROJECT, 2023
** current
** File description:
** return_value
*/

#include "shell.h"

static char *get_clean_local_string(char *value)
{
    if (value[0] != '(')
        return value;
    char *str = strdup(value + 1);
    for (int i = 0; str[i]; i++)
        if (str[i] == ':')
            str[i] = ' ';
    str[strlen(str) - 1] = '\0';
    return str;
}

static char *get_var_string(char *var, special_var_t special_var)
{
    int len = strlen(var);

    if (strcmp(var, "=") == 0)
        return "$";
    for (int i = 0; special_var->local[i]; i++)
        if (strncmp(var, special_var->local[i], len) == 0)
            return get_clean_local_string(special_var->local[i] + len);
    for (int i = 0; special_var->env[i]; i++)
        if (strncmp(var, special_var->env[i], len) == 0)
            return (special_var->env[i] + len);
    return NULL;
}

static int replace_exit_code(char **return_str, char *arg, int exit_code,
    int index)
{
    if (strncmp(arg + index, "$?", 2) == 0) {
        my_asprintf(return_str, "%.*s%d%s",
            index, arg, exit_code, arg + index + 2);
        return 1;
    }
    return 0;
}

static char *replace_var(char *arg, int *index, special_var_t special_var)
{
    int len = 1;
    char *var_name;
    char *return_str;
    char *var_string;

    if (replace_exit_code(&return_str, arg, special_var->exit_code, *index))
        return return_str;
    for (; arg[*index + len] && my_str_isalpha(&(arg[*index + len]));len++);
    my_asprintf(&var_name, "%.*s%c", len - 1, (arg + *index + 1), '=');
    my_asprintf(&return_str, "%.*s", (*index), arg);
    var_string = get_var_string(var_name, special_var);
    if (var_string == NULL) {
        *index = -85;
        return arg;
    }
    my_asprintf(&return_str, "%s%s%s", return_str,
        var_string, arg + *index + len);
    return return_str;
}

char **search_special_var(char **args, shell_t *shell)
{
    special_var_t special_var = malloc(sizeof(struct special_variable_s));
    special_var->env = shell->env;
    special_var->local = shell->local;
    special_var->exit_code = shell->exit_code;
    for (int i = 0, j = 0; args[i]; j++){
        if (j == -84) {
            my_eprintf("Undefined variable.\n");
            return NULL;
        }
        if (!args[i][j]){
            i++;
            j = -1;
            continue;
        }
        if (args[i][j] == '$'){
            args[i] = replace_var(args[i], &j, special_var);
            continue;
        }
    }
    return args;
}
