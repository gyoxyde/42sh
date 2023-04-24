/*
** EPITECH PROJECT, 2022
** lib
** File description:
** lib
*/

#include "my_printf.h"

char *my_strncpy(char *dest, char const *src, unsigned int n)
{
    unsigned int i = 0;
    unsigned int longueur = my_strlen(src);

    for (;i < n; ++i){
        dest[i] = src[i];
    }
    if (n > longueur){
        dest[i] = '\0';
    }
    return dest;
}

int my_strncmp(char *a, char *b, int n)
{
    if (a == NULL || b == NULL)
        return -1;
    int i = 0;
    char *file1 = my_strdup(a);
    char *file2 = my_strdup(b);
    while (file1[0] && file2[0] && (file1[0] == file2[0] ||
        file1[0] + 32 == file2[0] || file1[0] == file2[0] + 32) && i < n)
        file1++, file2++, i++;
    if (i == n)
        return 0;
    if (((int)file1[0] >= 65 && (int)file1[0] <= 90) &&
        ((int)file2[0] >= 97 && (int)file1[0] <= 122))
        return ((int)file1[0] + 32) - (int)file2[0];
    if (((int)file2[0] >= 65 && (int)file2[0] <= 90) &&
        ((int)file1[0] >= 97 && (int)file1[0] <= 122))
        return (int)file1[0] - ((int)file2[0] + 32);
    return (int)file1[0] - (int)file2[0];
}

char *my_strdup(char const *src)
{
    int len = my_strlen(src);
    char *str = malloc(sizeof(char) * (len + 1));
    if (len == 0){
        str[0] = '\0';
        return str;
    }

    for (int i = 0; src[i]; i++)
        str[i] = src[i];
    str[len] = '\0';
    return str;
}

int my_strisnum(char *str)
{
    int i = (str[0] == '-') ? 1 : 0;
    int len = my_strlen(str);
    if (len == 0)
        return 0;
    for (; str[i] && (str[i] >= '0' && str[i] <= '9'); i++);
    return (int)(i == len);
}

int get_nbr(char *str)
{
    int i = 0;
    if (str[0] == '-')
        i = 1;
    int nbr1 = 0;
    int nbr = 0;
    if (i == 1)
        nbr = -1;
    for (; str[i]; i++){
        nbr1 *= 10;
        nbr1 += str[i] - '0';
    }
    if (nbr == -1)
        nbr1 *= -1;
    return (nbr1);
}
