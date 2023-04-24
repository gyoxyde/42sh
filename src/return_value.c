/*
** EPITECH PROJECT, 2023
** current
** File description:
** return_value
*/

#include "../include/my.h"

char **search_return_val(char **args, var_t m)
{
    for (int i = 0, j = 0; args[i]; j++){
        if (!args[i][j]){
            i++;
            j = -1;
            continue;
        }
        if (args[i][j] == '$' && args[i][j + 1] == '?'){
            char *number = its_main(number, m->return_value);
            char *before = malloc(sizeof(char) * j + 1);

            before = my_strncpy(before, args[i], j);
            before[j] = '\0';
            args[i] += j + 2;
            args[i] = my_strcat(before, my_strcat(number, args[i]));
            i++;
            j = -1;
            continue;
        }
    }
    return args;
}
