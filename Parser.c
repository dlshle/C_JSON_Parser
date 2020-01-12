#include <stdio.h>
#include <stdlib.h>
#include "JsonObject.h"
#include "JsonArray.h"
#include "ErrorHandler.h"
#include "TokenList.h"
#include "TokenTypes.h"

#define COMMA_N_OBJ (SEP_COMMA | END_OBJECT)
int obj_expected_types[10] = {
	COMMA_N_OBJ,
	0, // NO NEED TO HANDLE END_OBJECT HERE(handled in parse_obj function)
	COMMA_N_OBJ,
	0, // NO NEED TO HANDLE END_ARRAY HERE(handled in parse_array function)
	COMMA_N_OBJ,
	COMMA_N_OBJ,
	((SEP_COMMA | END_OBJECT) | (SEP_COLON)), //as val or as key
	COMMA_N_OBJ,
	(BEGIN_OBJECT | BEGIN_ARRAY | J_NULL | NUMBER | STRING | BOOLEAN),
	(STRING)
};

#define COMMA_N_ARR (SEP_COMMA | END_ARRAY)
int arr_expected_types[10] = {
	COMMA_N_ARR,
	0,
	COMMA_N_ARR,
	0,
	COMMA_N_ARR,
	COMMA_N_ARR,
	COMMA_N_ARR,
	COMMA_N_ARR,
	0, //sep_col should not appear here but just to fit the arr size
	(BEGIN_OBJECT | BEGIN_ARRAY | J_NULL | NUMBER | STRING | BOOLEAN)
};

char C_TRUE = 1;
char C_FALSE = 0;
char C_NULL = 0;

int get_expected_types(enum TokenType type, int obj_flag) {
	int index = 0;
	while (type & 1 == 0) {
		type >>= 1;
		index++;
	}
	return (obj_flag?obj_expected_types[index]:arr_expected_types[index]);
}

void check_expected(enum TokenType type, int expected) {
	if (type & expected == 0)
		handle_error("Parser error: unexpected token.", 1);
}

struct JsonObject* parse_token_list(struct TokenList *list) {
	if (list == NULL)
		handle_error("Parser error: null token list.", 1);
	if (list_next_pair(list)->type != BEGIN_OBJECT)
		handle_error("Parser error: unexpected root token.", 1);
	return parse_json_obj(list);
}

// assume already encountered BEGIN_OBJECT
struct JsonObject* parse_json_obj(struct TokenList *list) {
	struct JsonObject *obj = init_json_object();
	char *key;
	int expected = get_expected_types(BEGIN_OBJECT, 1);
	while (list_has_more(list)) {
		struct TokenPair *pair = list_next_pair(list);
		enum TokenType type = pair->type;
		char *token = pair->value;
		switch (type) {
			case BEGIN_OBJECT:
				check_expected(type, expected);
				json_obj_put(obj, key, (char*)(parse_json_obj(list)), V_OBJECT);
				expected = get_expected_types(type, 1);
				break;
			case END_OBJECT:
				check_expected(type, expected);
				return obj;
			case BEGIN_ARRAY:
				check_expected(type, expected);
				json_obj_put(obj, key, (char*)(parse_json_arr(list)), V_ARRAY);
				expected = get_expected_types(type, 1);
				break;
			case J_NULL:
				check_expected(type, expected);
				json_obj_put(obj, key, &C_NULL, V_NULL);
				expected = get_expected_types(type, 1);
				break;
			case NUMBER:
				check_expected(type, expected);
				json_obj_put(obj, key, token, V_NUMBER);
				expected = get_expected_types(type, 1);
				break;
			case STRING:
				check_expected(type, expected);
				if ((list->token_list[list->pos-1])->type == SEP_COLON) {
					json_obj_put(obj, key, token, V_STRING);
					expected = SEP_COMMA | END_OBJECT;
				} else {
					key = token;
					expected = SEP_COLON;
				}
				break;
			case BOOLEAN:
				check_expected(type, expected);
				json_obj_put(obj, key, (token[0] == 't'?&C_TRUE:&C_FALSE), V_STRING);
				expected = get_expected_types(type, 1);
				break;
			case SEP_COLON:
				check_expected(type, expected);
				expected = get_expected_types(type, 1);
				break;
			case SEP_COMMA:
				check_expected(type, expected);
				expected = get_expected_types(type, 1);
				break;
			case END_DOCUMENT:
				check_expected(type, expected);
				return obj;
			default:
				handle_error("Parser error: unexpected token while parsing json object.", 1);
		}
	}
	handle_error("Parser error: incomplete json format(object).", 1);
}

// assume already encountered BEGIN_ARRAY
struct JsonArray* parse_json_arr(struct TokenList *list) {
	int expected = get_expected_types(BEGIN_ARRAY, 0);
	struct JsonArray *arr = init_json_array();
	while (list_has_more(list)) {
		struct TokenPair *pair = list_next_pair(list);
		enum TokenType type = pair->type;
		char *token = pair->value;
		switch (type) {
			case BEGIN_OBJECT:
				check_expected(type, expected);
				json_arr_append(arr, (char*)(parse_json_obj(list)), V_OBJECT);
				expected = get_expected_types(type, 0);
				break;
			case BEGIN_ARRAY:
				check_expected(type, expected);
				json_arr_append(arr, (char*)(parse_json_arr(list)), V_ARRAY);
				expected = get_expected_types(type, 0);
				break;
			case J_NULL:
				check_expected(type, expected);
				json_arr_append(arr, &C_NULL, V_NULL);
				expected = get_expected_types(type, 0);
				break;
			case NUMBER:
				check_expected(type, expected);
				json_arr_append(arr, token, V_NUMBER);
				expected = get_expected_types(type, 0);
				break;
			case STRING:
				check_expected(type, expected);
				json_arr_append(arr, token, V_STRING);
				expected = get_expected_types(type, 0);
				break;
			case BOOLEAN:
				check_expected(type, expected);
				json_arr_append(arr, (token[0] == 't'?&C_TRUE:&C_FALSE), V_STRING);
				expected = get_expected_types(type, 0);
				break;
			case SEP_COMMA:
				check_expected(type, expected);
				expected = get_expected_types(type, 1);
				break;
			case END_DOCUMENT:
				check_expected(type, expected);
				return arr;
			default:
				handle_error("Parser error: unexpected token while parsing json array.", 1);
		}
	}
	handle_error("Parser error: incomplete json format(array).", 1);
}
