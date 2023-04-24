/*
** EPITECH PROJECT, 2022
** my_revstr
** File description:
** reverse a string
*/

int my_strlen(char const *str);

void my_swap2 (char *a, char *b)
{
    char tempo = *a;
    *a = *b;
    *b = tempo;
}

char *my_revstr (char *str)
{
    int longueur = my_strlen(str);
    int compteur = 0;
    int compteur_inv = longueur - 1;
    for (; compteur_inv > compteur; ++compteur, --compteur_inv){
        my_swap2(&str[compteur], &str[compteur_inv]);
    }
    return (str);
}
