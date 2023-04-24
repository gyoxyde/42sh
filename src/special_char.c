/*
** EPITECH PROJECT, 2023
** current
** File description:
** special_char
*/

#include "../include/my.h"

// static int count_separator(char *str)
// {
//     int count = 0;

//     for (int i = 0; str[i]; i++){
//         if (){
//             count++;
//             continue;
//         }
//         if (str[i] == ' ' && (str[i + 1] != ';' && str[i + 1] != '<' &&
//            str[i + 1] != '>')  || (str[i] == ';' && str[i + 1] != ' ') ||
//            str[i] == '|' || str[i] == '<' ||
//             str[i] == '>'){
//             count++;
//             continue;
//         }
//     }

//     return count;
// }

// char **advanced_to_word_array(char *str)
// {
//     int count = 1;
//     char *copy = my_strdup(str);

//     count = count_separator(str);
//     char **dest = malloc(sizeof(char *) * (count + 1));
//     dest[count] = NULL;
//     for (int i = 0, len = 0; i < count; i++){
//         for (len = 0; str[0] && str[0] != c; str++, len++);
//         str ++;
//         dest[i] = malloc(sizeof(char) * len + 1);
//         dest[i][len] = '\0';
//         dest[i] = my_strncpy(dest[i], copy, len);
//         copy += len + 1;
//     }
//     return dest;
// }
