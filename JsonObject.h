#ifndef __JSON_OBJ_H__
#define __JSON_OBJ_H__
// define the JSON object struct using a customized map
#include "TokenTypes.h"

/*
 * JsonObject Value Specifications:
 * A JsonObject value could be one of the following types:
 *  Object, Array, NUMBER, STRING, BOOLEAN, NULL.
 * The corresponding TokenType enum defines the type for the object value.
 * The vals pointer(of pointers) points to the address of a JsonObject value.
 * type		value_type
 * STRING	char*
 * NUMBER	char*(string rep. of #)
 * BOOLEAN	char* (1 == true | 0 == false)
 * NULL		char* (random #)
 * OBJECT	struct JsonObject* (pointer to the object)
 * ARRAY	struct JsonArray*
*/

enum JsonValueType {
	V_STRING, V_NUMBER, V_BOOLEAN, V_NULL, V_OBJECT, V_ARRAY
};

struct JsonObject {
	char **keys;
	// vals is an array of char pointers
	char **vals;
	enum JsonValueType *val_types;
	int size;
	int cap;
};

struct JsonObject* init_json_object();
// returns the index of a key or -1 if key DNE
int json_obj_index_key(struct JsonObject *obj, char *key);
/*
 * json_obj_put puts a new k-v-t pair to the map
 * it checks whether there's a confliction key in the map first and returns
 * whether the operation is successful.
 * char *val is the pointer to the json object value
*/
int json_obj_put(struct JsonObject *obj, char *key, char *val, enum JsonValueType type);
int json_obj_remove(struct JsonObject *obj, char *key);
void free_json_obj(struct JsonObject *obj, int free_val);
#endif
