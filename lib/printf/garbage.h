/*
** EPITECH PROJECT, 2023
** PROJETS
** File description:
** garbage
*/
#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <stdint.h>

typedef struct garbage_s{
    void *data;
    struct garbage_s *next;
    struct garbage_s *prev;
}garbage_t;

typedef garbage_t *g_llist;
g_llist g_create(void *data);
g_llist g_delete_begin(g_llist list);
g_llist g_insert_end(void *data, g_llist list);
g_llist *get_llist(void);
void my_free_all(void);
void my_free(void *pointer);
void *my_malloc(size_t size);
