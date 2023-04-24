/*
** EPITECH PROJECT, 2022
** my_put_nbr
** File description:
** my_put_nbr
*/
int my_putchar(char c);

int my_put_nbr(int n)
{
    if (n < 0) {
        my_putchar('-');
        n = -n;
    }
    if (n > 9) {
        my_put_nbr(n / 10);
    }
    my_putchar('0'+ (n % 10));
    return 0;
}
