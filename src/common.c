#include "common.h"

#include <string.h>

void da_init(DynArr *da, uint32_t elsize)
{
	da->data = NULL;
	da->elsize = elsize;
	da->elcount = 0;
	da->cap = 0;
}

void da_clean(DynArr const* da)
{
	if(da->data) free(da->data);
}

void da_alloc(DynArr *da, uint32_t i, Error *err)
{
	da->elcount += i;
	if(da->elcount >= da->cap) {
		da->cap = da->elcount * 2;
		da->data = realloc(da->data, da->cap * da->elsize);
		if(!da->data) {
			fprintf(stderr, "OOM!\n");
			*err = ERROR_OOM;
			goto RET;
		}
	}

RET:
	return;
}


void *da_at(DynArr const* da, uint32_t i)
{
	return ((char *) da->data) + i * da->elsize;
}

void *da_from_back(DynArr const* da, uint32_t i)
{
	return ((char *) da->data) + (da->elcount - i - 1) * da->elsize;
}

void da_push(DynArr *da, void const* el, Error *err)
{
	da_alloc(da, 1, err);
	if(*err) goto RET;

	memcpy(da_from_back(da, 0), el, da->elsize);	
RET:
	return;
}

#ifndef LIB
int main(void)
{
	printf("This Utility cannot be used as a standalone program.\n");
	return 1;
}
#endif //LIB
