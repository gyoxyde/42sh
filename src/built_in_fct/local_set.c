/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** local_set
*/

#include "shell.h"

static void add_inexistant(shell_t *shell, char *key, char *value)
{
    int index = get_local_index(shell->local);
    if (value)
        asprintf(&shell->local[index], "%s=%s", key, value);
    else
        asprintf(&shell->local[index], "%s=", key);
}

void add_couples(shell_t *shell, char **keys, char **values)
{
    int index;
    for (int i = 0; keys[i]; i++) {
        if (my_getlocal(shell, keys[i]) == NULL) {
            add_inexistant(shell, keys[i], values[i]);
            return;
        }
        for (int j = 0; shell->local[j]; j++)
            index = (strncmp(shell->local[j], keys[i], strlen(keys[i])) == 0)
                ? j : -1;
        if (values[i])
            asprintf(&shell->local[index], "%s=%s", keys[i], values[i]);
        else
            asprintf(&shell->local[index], "%s=", keys[i]);
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
