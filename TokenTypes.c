#include "TokenTypes.h"
#include <stdio.h>
#include <stdlib.h>

struct TokenPair* init_token_pair(enum TokenType type, char *value) {
	struct TokenPair *pair = malloc(sizeof(struct TokenPair));
	pair->type = type;
	pair->value = value;
	return pair;
}


char* get_token_type_str(enum TokenType type) {
	switch (type) {
		case BEGIN_OBJECT:
			return "BEGIN_OBJECT";
    case END_OBJECT:
			return "END_OBJECT";
    case BEGIN_ARRAY:
			return "BEGIN_ARRAY";
    case END_ARRAY:
			return "END_ARRAY";
    case J_NULL:
			return "J_NULL";
    case NUMBER:
			return "NUMBER";
    case STRING:
			return "STRING";
    case BOOLEAN:
			return "BOOLEAN";
    case SEP_COLON:
			return "SEP_COLON";
    case SEP_COMMA:
			return "SEP_COMMA";
    case END_DOCUMENT:
			return "END_DOCUMENT";
	}
	return "UNKNOWN";
}


void print_token_pair(struct TokenPair *pair) {
	printf("TokenPair { type: %s value: \"%s\" }\n", get_token_type_str(pair->type), 
	pair->value);
}

void free_token_pair(struct TokenPair *pair, int free_val) {
	if (free_val)
		free(pair->value);
	free(pair);
}
