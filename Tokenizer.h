#ifndef __TOKENIZER_H__
#define __TOKENIZER_H__

#include "TokenList.h"

struct TokenList *token_list;

void tokenize();
struct TokenPair* tokenize_token();
struct TokenPair* tokenize_string();
struct TokenPair* tokenize_boolean();
struct TokenPair* tokenize_null();
struct TokenPair* tokenize_number();

#endif
