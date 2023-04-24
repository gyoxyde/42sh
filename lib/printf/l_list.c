/*
** EPITECH PROJECT, 2022
** pushswap
** File description:
** llist
*/

#include "./my_printf.h"

l_list create(char *data)
{
    l_list new_node = malloc(sizeof(l_list));

    new_node->data = data;
    new_node->next = NULL;
    new_node->prev = NULL;

    return new_node;
}

l_list insert_begin(char *data, l_list list)
{
    l_list new_node = create(data);

    if (new_node){
        if (list == NULL){
            new_node->next = new_node;
            new_node->prev = new_node;
            list = new_node;
            return list;
        }
        list->prev->next = new_node;
        new_node->prev = list->prev;
        new_node->next = list;
        list->prev = new_node;
        list = new_node;
    }
    return list;
}

l_list insert_end(char *data, l_list list)
{
    l_list new_node = create(data);
    if (list == NULL){
        new_node->next = new_node;
        new_node->prev = new_node;
        list = new_node;
        return list;
    }
    list->prev->next = new_node;
    new_node->prev = list->prev;
    new_node->next = list;
    list->prev = new_node;
    return list;
}

l_list delete_begin(l_list list)
{
    if (list == NULL)
        return list;
    else if (list->next == list){
        list = NULL;
        return list;
    }

    l_list temp = list;
    list->prev->next = list->next;
    list->next->prev = list->prev;
    list = list->next;

    free(temp);
    temp = NULL;
    return list;
}
