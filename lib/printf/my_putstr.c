/*
** EPITECH PROJECT, 2022
** my_putstr
** File description:
** my_putstr
*/

int my_strlen(char *str);
int my_putchar(char c);

int my_putstr(char *str)
{
    for (int c = 0; str[c] != '\0'; ++c){
        my_putchar(str[c]);
    }
    return my_strlen(str);
}
