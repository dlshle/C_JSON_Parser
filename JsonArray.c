#include <stdlib.h>
#include <stdio.h>
#include "JsonObject.h"
#include "JsonArray.h"
#include "ErrorHandler.h"
#include "JsonStringifyUtil.h"

#define EXPAND_FACTOR 1.5

int json_arr_expand(struct JsonArray *arr) {
	arr->elements = realloc(arr->elements, sizeof(char*) * arr->cap * EXPAND_FACTOR);
	if (!arr->elements)
		return 0;
	arr->types = realloc(arr->types, sizeof(enum JsonValueType) * arr->cap * EXPAND_FACTOR);
	if (!arr->types)
		return 0;
	arr->cap *= EXPAND_FACTOR;
	return 1;
}

void json_arr_check_cap(struct JsonArray *arr) {
	if (arr->size >= arr->cap)
		json_arr_expand(arr);
}

struct JsonArray* init_json_array() {
	struct JsonArray *arr = malloc(sizeof(struct JsonArray));
	if (arr == NULL)
		handle_error("JsonArray error: initialization failed.", 1);
	arr->size = 0;
	arr->cap = 5;
	arr->elements = malloc(sizeof(char*) * 5);
	arr->types = malloc(sizeof(enum JsonValueType) * 5);
	return arr;
}

int json_arr_append(struct JsonArray *arr, char *ele, enum TokenType type) {
	json_arr_check_cap(arr);
	int curr_size = arr->size++;
	arr->elements[curr_size] = ele;
	arr->types[curr_size] = type;
}

int json_arr_remove(struct JsonArray *arr, char *key) {
	// TODO maybe later
	return 0;
}

void free_json_array(struct JsonArray *arr, int free_val) {
	if (free_val) {
		for (int i = 0; i < arr->size; i++) {
			free(&arr->elements[i]);
		}
	}
	free(arr->elements);
	free(arr->types);
	free(arr);
}
