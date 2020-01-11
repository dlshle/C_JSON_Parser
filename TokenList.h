#include "TokenTypes.h"

struct TokenList {
	struct TokenPair **token_list;
	unsigned int pos;
	unsigned int size;
	unsigned int cap;
};

struct TokenList* init_token_list();
void list_add_pair(struct TokenList *list, struct TokenPair *pair);
struct TokenPair* list_peek_pair(struct TokenList *list);
struct TokenPair* list_next_pair(struct TokenList *list);
struct TokenPair* list_peek_prev_pair(struct TokenList *list);
int list_has_more(struct TokenList *list);
void list_print(struct TokenList *list);

void list_free(struct TokenList *list, int free_val);
