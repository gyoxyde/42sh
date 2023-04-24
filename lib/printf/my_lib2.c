/*
** EPITECH PROJECT, 2023
** PROJETS
** File description:
** my_lib2
*/

#include "my_printf.h"

char **to_word_array(char *str, char c)
{
    int count = 1;
    char *copy = my_strdup(str);

    for (int i = 0; str[i]; i++, count += (str[i] == c) ? 1 : 0);
    char **dest = malloc(sizeof(char *) * (count + 1));
    dest[count] = NULL;
    for (int i = 0, len = 0; i < count; i++){
        for (len = 0; str[0] && str[0] != c; str++, len++);
        str ++;
        dest[i] = malloc(sizeof(char) * len + 1);
        dest[i][len] = '\0';
        dest[i] = my_strncpy(dest[i], copy, len);
        copy += len + 1;
    }
    return dest;
}

int my_tablen(void **tab)
{
    int i = 0;
    for (; tab[i]; i++);
    return i;
}

int my_strcmp(char *a, char *b)
{
    if (my_strlen(a) != my_strlen(b))
        return 0;
    for (int i = 0; a[i]; i++){
        if (a[i] != b[i])
            return 0;
    }
    return 1;
}

char *my_cleanstr(char *src)
{
    char *dest = malloc(sizeof(char) * my_strlen(src) + 1);
    int j = 0;
    int i = 0;

    for (int m = 0; src[m]; m++)
        if (src[m] == '\t')
            src[m] = ' ';
    while (src[0] == ' ')
        src++;
    while (src[i]) {
        if ((src[i] == ' ' && src[i + 1] == ' ') ||
            (src[i] == ';' && src[i + 1] == ';'))
            i++;
        else
            dest[j++] = src[i++];
    }
    dest[j] = '\0';
    for (int m = my_strlen(dest) - 1; dest[m] == ' '; m--)
        dest[m] = '\0';
    return dest;
}

int my_isalpha(char *src)
{
    int i = 0;

    if ((src[i] < 'A' || (src[i] > 'Z' && src[i] < 'a') || src[i] > 'z') &&
        src[i] != '_')
        return 84;
    while (src[i] != '\0' &&
        ((src[i] >= 'a' && src[i] <= 'z') || (src[i] >= 'A' && src[i] <= 'Z')
        || (src[i] >= '0' && src[i] <= '9') || src[i] == '.' || src[i] == '_'
        || src[i] == '/'))
        i++;
    return (i == (int)my_strlen(src));
}
