// define the JSON array struct using a dynamic array
#include "JsonObject.h"

struct JsonArray {
	char **elements;
	enum JsonValueType *types;
	int size;
	int cap;
};

struct JsonArray* init_json_array();
int json_arr_append(struct JsonArray *arr, char *ele, enum TokenType type);
int json_arr_remove(struct JsonArray *arr, char *ele);
void free_json_array(struct JsonArray *arr, int free_val);
