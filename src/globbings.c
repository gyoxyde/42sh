/*
** EPITECH PROJECT, 2023
** 42sh
** File description:
** globbings
*/

#include "shell.h"
#include <glob.h>

char *concat_glob(glob_t globbuf, char *command)
{
    char *tmp = "";

    if (globbuf.gl_pathc == 0) {
        my_eprintf("%s: No match.\n", command);
        return NULL;
    }
    for (size_t i = 0; i < globbuf.gl_pathc; i++) {
        tmp = my_strcat(tmp, globbuf.gl_pathv[i]);
        tmp = my_strcat(tmp, " ");
    }
    return tmp;
}

char *parse_glob(char *str, char *command)
{
    for (int i = 0; str[i]; i++) {
        if (str[i] == '*' || str[i] == '?' || str[i] == '[' || str[i] == ']') {
            glob_t globbuf;
            glob(str, GLOB_NOMATCH, NULL, &globbuf);
            return concat_glob(globbuf, command);
        }
    }
    return str;
}

char **change_globbings(char **array, shell_t *shell)
{
    char *str = NULL;

    for (int i = 0; array[i]; i++) {
        str = parse_glob(array[i], array[0]);
        if (str != NULL)
            array[i] = str;
        else {
            shell->temp_exit_code = 1;
            return NULL;
        }
        str = NULL;
    }
    return array;
}
