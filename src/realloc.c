/*
** EPITECH PROJECT, 2020
** PSU_2019_malloc
** File description:
** realloc
*/

#include "../include/malloc_struct.h"

chunk_t *get_block(void *ptr)
{
    return (chunk_t *)ptr - 1;
}

chunk_t *fusion(chunk_t *ptr)
{
    if (ptr->next && ptr->next->free) {
        ptr->size += ptr->next->size + CHUNK_SIZE;
        ptr->next = ptr->next->next;
        if (ptr->next)
            ptr->next->prev = ptr;
    }
    return ptr;
}

void free(void *ptr)
{
    chunk_t *tmp;

    if (!ptr)
        return;
    tmp = get_block(ptr);
    if (!tmp)
        return;
    if (tmp->prev && tmp->prev->free)
        tmp = fusion(tmp->prev);
    if (tmp->next)
        fusion(tmp);
    tmp->free = 1;
}

void *realloc(void *ptr, size_t size)
{
    chunk_t *tmp = NULL;
    void *new_ptr = NULL;

    if (!ptr)
        return malloc(size);
    tmp = get_block(ptr);
    if (tmp->size >= size)
        return ptr;
    new_ptr = malloc(size);
    if (!new_ptr)
        return NULL;
    memcpy(new_ptr, ptr, tmp->size);
    free(ptr);
    return new_ptr;
}

void *reallocarray(void *ptr, size_t nmemb, size_t size)
{
    chunk_t *tmp;
    void *new_ptr;

    if (!ptr)
        return malloc(size * (nmemb));
    tmp = get_block(ptr);
    if (tmp->size >= size * (nmemb))
        return ptr;
    new_ptr = malloc(size * (nmemb));
    if (!new_ptr)
        return NULL;
    memcpy(new_ptr, ptr, tmp->size);
    free(ptr);
    return new_ptr;
}
