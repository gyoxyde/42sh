/*
** EPITECH PROJECT, 2022
** my_intlen
** File description:
** my_intlen
*/

unsigned int my_intlen(long int n)
{
    int c = 0;
    if (n < 0){
        n = -n;
        c++;
    }
    for (; n > 1; c++, n /= 10);
    return c;
}
