/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** local_utils
*/

#include "shell.h"

char *set_errors(int type, shell_t *shell)
{
    if (type == BEGIN_LETTER)
        my_eprintf("set: Variable name must begin with a letter.\n");
    if (type == ALPHANUM_CHAR) {
        my_eprintf("set: Variable name must");
        my_eprintf(" contain alphanumeric characters.\n");
    }
    if (type == PARENTHESIS_LEFT)
        my_eprintf("Too many ('s.\n");
    if (type == PARENTHESIS_RIGHT)
        my_eprintf("Too many )'s.\n");
    if (type == QUOTES)
        my_eprintf("Unmatched \".\n");
    shell->temp_exit_code = 1;
    return NULL;
}

void move_string(char *str, int *i)
{
    char c = str[*i];

    if (*i > 0 && (c == '=' || c == '(' || c == ')') && str[*i - 1] == ' ') {
        for (int j = (*i) - 1; str[j]; j++)
            str[j] = str[j + 1];
        *i = -1;
        return;
    }
    if ((c == '=' || c == '(') && str[*i + 1] == ' ') {
        for (int j = (*i) + 1; str[j]; j++)
            str[j] = str[j + 1];
        *i = -1;
    }
}

char **get_flat_input(char **user_input, shell_t *shell)
{
    char *str = strdup(my_strcat(user_input[1], " "));
    int quotes = 0;
    char c;
    if (user_input[1] != NULL)
        for (int i = 2; user_input[i]; i++)
            my_asprintf(&str, "%s%s ", str, user_input[i]);
    for (int i = 0; str[i]; i++)
        move_string(str, &i);
    for (int i = 0, parenth = 0; str[i]; i++) {
        c = str[i];
        if (c == '\"') quotes++;
        parenth += (c == '(') ? 1 : (c == ')') ? -1 : 0;
        if (parenth < 0) set_errors(PARENTHESIS_RIGHT, shell);
        if (parenth > 1) set_errors(PARENTHESIS_LEFT, shell);
        if (parenth < 0 || parenth > 1) return NULL;
        str[i] = (c == ' ' && parenth != 0) ? ':' : c;
    }
    if (quotes % 2 != 0) set_errors(QUOTES, shell);
    if (quotes % 2 != 0) return NULL;
    return my_str_to_word_array(clean_str(str), ' ');
}

int get_local_index(char **local)
{
    int i = 0;

    for (; local[i]; i++);
    return i;
}

void order_local(char **keys, char **values, int len)
{
    for (int i = 0, j = 1; i < len; j++) {
        if (j >= len) {
            j = i;
            i++;
            continue;
        }
        if (strcmp(keys[i], keys[j]) > 0) {
            my_strswap(&keys[i], &keys[j]);
            my_strswap(&values[i], &values[j]);
        }
    }
}
