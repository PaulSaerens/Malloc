/*
** EPITECH PROJECT, 2020
** PSU_2019_malloc
** File description:
** malloc_struct
*/

#ifndef MALLOC_STRUCT_H_
#define MALLOC_STRUCT_H_

#include <stddef.h>
#include <stdio.h>
#include <string.h>


typedef struct chunk_t
{
    size_t size;
    int free;

    struct chunk_t *next;
    struct chunk_t *prev;
} chunk_t;

#define CHUNK_SIZE sizeof(chunk_t)

void *global_head;

void free(void *ptr);

void *malloc(size_t size);
void *calloc(size_t nmemb, size_t size);
void *realloc(void *ptr, size_t size);
void *reallocarray(void *ptr, size_t nmemb, size_t size);

chunk_t *get_block(void *ptr);
chunk_t *find_block_best_fit_algo(chunk_t **last, size_t size);
chunk_t *split_chunk(chunk_t *ptr, size_t size);
chunk_t *extend_heap(chunk_t *last, size_t size);

#endif /* !MALLOC_STRUCT_H_ */
