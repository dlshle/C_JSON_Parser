#include <stdio.h>
#include <stdlib.h>
#include "TokenList.h"

#define EXPAND_FACTOR 1.5

struct TokenList* init_token_list() {
	struct TokenList *list = malloc(sizeof(struct TokenList));
	list->pos = 0;
	list->size = 0;
	list->token_list = malloc(sizeof(struct TokenPair*) * 10);
	list->cap = 10;
}

void list_add_pair(struct TokenList *list, struct TokenPair *pair) {
	if (list->size == list->cap) {
		if (!extend_cap(list)) {
			//error: capacity extend failed
			exit(1);
		}
	}
	list->token_list[list->size++] = pair;
}

struct TokenPair* list_peek_pair(struct TokenList *list) {
	return list->token_list[list->pos];
}

struct TokenPair* list_next_pair(struct TokenList *list) {
	if (list->pos >= list->size)
		return -1;
	return list->token_list[list->pos++];
}

struct TokenPair* list_peek_prev_pair(struct TokenList *list) {
	if (list->pos == 0)
		return -1;
	return list->token_list[list->pos-1];
}

int list_has_more(struct TokenList *list) {
	return list->pos < list->size;
}

void list_print(struct TokenList *list) {
	for (int i = 0; i < list->size; i++) {
		printf("%d of %d:\n", i, list->size);
		print_token_pair(list->token_list[i]);
	}
}

int extend_cap(struct TokenList *list) {
	list->token_list = realloc(list->token_list, (list->cap * EXPAND_FACTOR) * sizeof(struct TokenPair*));
	list->cap *= EXPAND_FACTOR;
	return list->token_list != NULL;
}

void list_free(struct TokenList *list, int free_val) {
	for (int i = 0; i < list->size; i++) {
		free_token_pair(list->token_list[i], free_val);
	}
	free(list->token_list);
}
