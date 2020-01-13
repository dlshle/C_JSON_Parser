#include <stdlib.h>
#include <stdio.h>
#include "JsonObject.h"
#include "ErrorHandler.h"
#include "JsonArray.h"
#include "JsonStringifyUtil.h"

#define EXPAND_FACTOR 1.5

void json_obj_check_cap(struct JsonObject *obj) {
	if (obj->size >= obj->cap)
		json_obj_expand(obj);
}

int json_obj_same_key(char *key, char *tar) {
	int count = 0;
	while (key[count++] != '\0') {
		if (tar[count] == '\0')
			return 0;
		if (key[count] != tar[count])
			return 0;
	}
	return tar[count] == '\0';
}

struct JsonObject* init_json_object() {
	struct JsonObject *obj = malloc(sizeof(struct JsonObject));
	obj->size = 0;
	obj->cap = 5;
	obj->keys = malloc(sizeof(char*) * 5);
	obj->vals = malloc(sizeof(char*) * 5);
	obj->val_types = malloc(sizeof(enum JsonValueType) * 5);
	return obj;
}

int json_obj_index_key(struct JsonObject *obj, char *key) {
	for (int i = 0; i < obj->size; i++)
		if (json_obj_same_key(key, obj->keys[i]))
			return i;
	return -1;
}

int json_obj_put(struct JsonObject *obj, char *key, char *val, enum JsonValueType type) {
	if (json_obj_index_key(obj, key) > -1)
		return 0;
	json_obj_check_cap(obj);
	int curr_size = obj->size++;
	obj->keys[curr_size] = key;
	obj->vals[curr_size] = val;
	obj->val_types[curr_size] = type;
}

int json_obj_remove(struct JsonObject *obj, char *key) {
	// TODO
	return 0;
}

void free_json_obj(struct JsonObject *obj, int free_val) {
	if (free_val) {
		for (int i = 0; i < obj->size; i++) {
			free(&obj->keys[i]);
			free(&obj->vals[i]);
		}
	}
	free(obj->keys);
	free(obj->vals);
	free(obj->val_types);
	free(obj);
}

int json_obj_expand(struct JsonObject *obj) {
	obj->keys = realloc(obj->keys, sizeof(char*) * obj->cap * EXPAND_FACTOR);
	if (!obj->keys) {
		return 0;
	}
	obj->vals = realloc(obj->vals, sizeof(char*) * obj->cap * EXPAND_FACTOR);
	if (!obj->vals) {
		return 0;
	}
	obj->val_types = realloc(obj->val_types, sizeof(char*) * obj->cap * EXPAND_FACTOR);
	if (!obj->val_types) {
		return 0;
	}
	obj->cap *= EXPAND_FACTOR;
	return 1;
}
