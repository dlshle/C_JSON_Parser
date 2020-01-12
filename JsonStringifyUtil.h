#include "StringBuffer.h"
#include "JsonObject.h"
#include "JsonArray.h"

void print_json_obj(struct JsonObject *obj);
void print_json_arr(struct JsonArray *arr);
void print_json_obj_ent(struct JsonObject *obj, int index);

char* stringify_json_obj(struct JsonObject *obj);
void append_json_obj_indent(struct StringBuffer *buffer, struct JsonObject *obj, int indent);
char* stringify_json_arr(struct JsonArray *arr);
void append_json_arr_indent(struct StringBuffer *buffer, struct JsonArray *arr, int indent);
char* stringify_json_obj_entry(struct JsonObject *obj, int index);
void append_json_obj_entry_indent(struct StringBuffer *buffer, struct JsonObject *obj, int index, int indent);
