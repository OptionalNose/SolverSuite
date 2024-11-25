#pragma once

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

typedef enum {
	ERROR_OK,
	
	ERROR_INVALID,
	ERROR_NAN,
	ERROR_OOM,
} Error;


typedef struct {
	void *data;
	uint32_t elsize;
	uint32_t elcount;
	uint32_t cap;
} DynArr;

void da_init(DynArr *da, uint32_t elsize);
void da_clean(DynArr const* da);

void da_alloc(DynArr *da, uint32_t i, Error *err);
void *da_at(DynArr const* da, uint32_t i);
void *da_from_back(DynArr const* da, uint32_t i);

void da_push(DynArr *da, void const* el, Error *err);

