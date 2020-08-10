/*
** EPITECH PROJECT, 2020
** PSU_2019_malloc
** File description:
** malloc
*/

#include <unistd.h>
#include "../include/malloc_struct.h"

chunk_t *find_block_best_fit_algo(chunk_t **last, size_t size)
{
    chunk_t *current = global_head;

    while (current && !(current->free && current->size >= size)) {
        *last = current;
        current = current->next;
    }
    return current;
}

chunk_t *split_chunk(chunk_t *ptr, size_t size)
{
    chunk_t *new = (void *)ptr + CHUNK_SIZE + size;

    if (!new)
        return ptr;
    new->size = ptr->size - size - CHUNK_SIZE;
    new->next = ptr->next;
    new->prev = ptr;
    new->free = 1;
    ptr->size = size;
    ptr->free = 0;
    if (ptr && ptr->next) {
        ptr->next->prev = new;
    }
    ptr->next = new;
    return ptr;
}

chunk_t *extend_heap(chunk_t *last, size_t size)
{
    int page = getpagesize();
    int calc = (((size + CHUNK_SIZE) / page) + 1) * page;
    chunk_t *tmp = sbrk(calc);

    if (tmp == (void *)-1)
        return NULL;
    if (last)
        last->next = tmp;
    tmp->prev = last;
    tmp->size = calc - CHUNK_SIZE;
    tmp->next = NULL;
    tmp->free = 0;
    tmp = split_chunk(tmp, size);
    return tmp;
}

void *malloc(size_t size)
{
    chunk_t *ptr = NULL;
    chunk_t *last = global_head;

    if (size <= 0)
        return NULL;
    if (!global_head) {
        ptr = extend_heap(NULL, size);
        if (ptr == NULL)
            return NULL;
        global_head = ptr;
    } else {
        ptr = find_block_best_fit_algo(&last, size);
        if (!ptr)
            ptr = extend_heap(last, size);
        else {
            if (ptr->size - size > CHUNK_SIZE)
                ptr = split_chunk(ptr, size);
            ptr->free = 0;
        }
    }
    return ptr + 1;
}

void *calloc(size_t nmemb, size_t size)
{
    size_t *new;

    new = malloc(nmemb * size);
    if (new && size > 0) {
        for (size_t i = 0; i < size; i += 1)
            new[i] = 0;
        return new;
    }
    else
        return NULL;
}
