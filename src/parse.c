#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "common.h"

#include "parse.h"

static char skip_ws(char const **input)
{
	while(isspace(*++*input));
	return **input;
}

void parse_lex(char const *input, parse_Token **tokens, uint32_t token_count, Error *err)
{
	DynArr token_list;
	da_init(&token_list, sizeof (parse_Token));

	
RET:
	*tokens = token_list.data;
	*token_count = token_list.elcount;	
	return;
}

#ifndef LIB
int main(void)
{
	printf("This Utility cannot be used as a standalone program.\n");
	return 1;
}
#endif //LIB
