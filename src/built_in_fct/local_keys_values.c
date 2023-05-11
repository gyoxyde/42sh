/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** local_keys_values
*/

#include "shell.h"

static int check_local_key_str(char *key, shell_t *shell)
{
    char c = key[0];
    if (!((c >= 'a' && c <= 'z') || (c == '\"' || c == '(' || c == ')') ||
        (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') ||
        (c == '_' || c == '.' || c == '=' || c == ':' || c == '\0'))) {
        set_errors(BEGIN_LETTER, shell);
        return 84;
    }
    for (int i = 1; key[i]; i++) {
        c = key[i];
        if (!((c >= 'a' && c <= 'z') || (c == '\"' || c == '(' || c == ')') ||
        (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') ||
        (c == '_' || c == '.' || c == '=' || c == ':'))) {
            set_errors(ALPHANUM_CHAR, shell);
            return 84;
        }
    }
    return 0;
}

char **get_keys(char **user_input, shell_t *shell)
{
    char **line;
    char **keys;
    int len = 0;

    for (int i = 0; user_input[i]; i++, len++);
    keys = malloc(sizeof(char *) * (len + 1));
    keys[len] = NULL;
    for (int i = 0; user_input[i]; i++) {
        if (user_input[i][0] == '=') {
            set_errors(BEGIN_LETTER, shell);
            return NULL;
        }
        line = my_str_to_word_array(user_input[i], '=');
        keys[i] = my_strdup(line[0]);
        if (check_local_key_str(keys[i], shell) == 84)
            return NULL;
    }
    return keys;
}

char **get_values(char **user_input, shell_t *shell)
{
    char **line;
    char **values;
    int len = 0;

    for (int i = 0; user_input[i]; i++, len++);
    values = malloc(sizeof(char *) * (len + 1));
    values[len] = NULL;
    for (int i = 0; user_input[i]; i++) {
        line = my_str_to_word_array(user_input[i], '=');
        if (line[1] == NULL)
            values[i] = my_strdup("");
        else
            values[i] = my_strdup(line[1]);
        if (check_local_key_str(values[i], shell) == 84) {
            return NULL;
        }
    }
    return values;
}
