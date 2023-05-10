/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** local
*/

#include "shell.h"

char *my_getlocal(shell_t *shell, char *key)
{
    int len = strlen(key);
    char *value = NULL;
    char **local = shell->local;
    int found = 0;

    for (int i = 0; local[i]; i++) {
        if (strncmp(local[i], key, len) == 0) {
            value = strdup(local[i] + len + 1);
            found = 1;
            break;
        }
    }
    if (found == 0)
        return NULL;
    else if (value == NULL)
        return "";
    return value;
}

static void display_values(char *value, char *key)
{
    bool parenthesis = false;

    printf("%s ", key);
    if (value == NULL)
        return;
    for (int i = 0; value[i]; i++)
        if (value[i] == ':')
            parenthesis = true;
    if (parenthesis == false)
        printf("%s", value);
    else
        for (int i = 0; value[i]; i++)
            (value[i] == ':') ? printf(" ") : printf("%c", value[i]);
}

int my_set_display(shell_t *shell)
{
    int len = get_local_index(shell->local);
    char **keys = malloc(sizeof(char *) * (len + 1));
    char **values = malloc(sizeof(char *) * (len + 1));
    char **local;
    for (int i = 0; shell->local[i]; i++) {
        local = my_str_to_word_array(shell->local[i], '=');
        keys[i] = local[0];
        values[i] = local[1];
    }
    keys[len] = NULL;
    values[len] = NULL;
    order_local(keys, values, len);
    for (int i = 0; keys[i]; i++) {
        display_values(values[i], keys[i]);
        printf("\n");
    }
    return 0;
}
