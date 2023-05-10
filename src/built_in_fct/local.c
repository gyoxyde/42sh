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

void add_couples(shell_t *shell, char **keys, char **values)
{
    int index;

    for (int i = 0; keys[i]; i++) {
        if (my_getlocal(shell, keys[i]) == NULL) {
            index = get_local_index(shell->local);
            if (values[i])
                asprintf(&shell->local[index], "%s=%s", keys[i], values[i]);
            else
                asprintf(&shell->local[index], "%s=", keys[i]);
            return;
        }
        for (int j = 0; shell->local[j]; j++) {
            index = (strncmp(shell->local[j], keys[i], strlen(keys[i])) == 0) ? j : -1;
        }
        if (values[i]) {
            asprintf(&shell->local[index], "%s=%s", keys[i], values[i]);
        } else {
            asprintf(&shell->local[index], "%s=", keys[i]);
        }
    }
}

int my_setlocal(shell_t *shell, char **array)
{
    char **local = shell->local;
    char **user_input;
    char **keys;
    char **values;

    if (array[1] == NULL) return my_set_display(shell);
    user_input = get_flat_input(array);
    if (user_input == NULL) return 84;
    keys = get_keys(user_input, shell);
    values = get_values(user_input, shell);
    if (keys == NULL || values == NULL) return 84;
    add_couples(shell, keys, values);
    return 0;
}
