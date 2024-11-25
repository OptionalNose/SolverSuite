#pragma once

#include "common.h"

typedef enum {
	parse_TOKEN_NONE,

	parse_TOKEN_LIT,
	parse_TOKEN_SYM,
	
	parse_TOKEN_ADD,
	parse_TOKEN_MUL,
	parse_TOKEN_SUB,
	parse_TOKEN_DIV,
	parse_TOKEN_EXP,

	parse_TOKEN_E,
	parse_TOKEN_I,
	parse_TOKEN_PI
} parse_TokenType;

typedef union {
	parse_TokenType type;

	struct {
		parse_TokenType type;
		double val;
	} lit;

	struct {
		parse_TokenType type;
		char *id;
	} sym;
} parse_Token;

void parse_lex(char const *input, parse_Token **tokens, uint32_t token_count, Error *err);
