#ifndef __PARSER_H__
#define __PARSER_H__

#include "JsonObject.h"
#include "JsonArray.h"
#include "TokenList.h"

int get_expected_types(enum TokenType type, int obj_flag);
void check_expected(enum TokenType type, int expected);
struct JsonObject* parse_token_list(struct TokenList *list);
struct JsonObject* parse_json_obj(struct TokenList *list);
struct JsonArray* parse_json_arr(struct TokenList *list);

#endif
