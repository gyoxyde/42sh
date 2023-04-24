/*
** EPITECH PROJECT, 2022
** my_strcmp
** File description:
** compare the strings. It returns 0 if they are the same.
*/

int my_strcmp(char const *s1, char const *s2)
{
    int i = 0;

    for (; s1[i] == s2[i] && s1[i] != '\0'; i++);
    return s1[i] - s2[i];
}
