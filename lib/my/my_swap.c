/*
** EPITECH PROJECT, 2022
** my_swap
** File description:
** swap
*/

void my_swap(int *a, int *b)
{
    int c = *a ;
    int d = *b ;
    *a = d ;
    *b = c ;
}

void my_strswap(char **a, char **b)
{
    char *c = *a ;
    char *d = *b ;
    *a = d ;
    *b = c ;
}
