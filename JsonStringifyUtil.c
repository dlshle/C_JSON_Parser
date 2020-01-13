#include <stdio.h>
#include <stdlib.h>
#include "JsonStringifyUtil.h"
#include "ErrorHandler.h"

// helper functions
char* stringify_string_buffer(struct StringBuffer *buffer) {
	char *str = buffer->string_buffer;
	free(buffer);
	return str;
}

void append_indent(struct StringBuffer *buffer, int indent) {
	while (indent-- > 0)
		buffer_append_char(buffer, '\t');
}

void append_json_string(struct StringBuffer *buffer, char *ptr) {
	buffer_append_string(buffer, ptr);
}

void append_json_number(struct StringBuffer *buffer, char *ptr) {
	buffer_append_string(buffer, ptr);
}

void append_json_null(struct StringBuffer *buffer, char *ptr) {
	buffer_append_string(buffer, "null");
}

void append_json_boolean(struct StringBuffer *buffer, char *ptr) {
	buffer_append_string(buffer, (*ptr?"true":"false"));
}

void append_json_value(struct StringBuffer *buffer, char *ptr, enum JsonValueType type, int indent) {
	switch(type)
	{
		case V_STRING:
			append_json_string(buffer, ptr);
			buffer_append_string(buffer, "(STRING)");
			return ;
		case V_NUMBER:
			append_json_number(buffer, ptr);
			buffer_append_string(buffer, "(NUMBER)");
			return ;
		case V_BOOLEAN:
			append_json_boolean(buffer, ptr);
			buffer_append_string(buffer, "(BOOLEAN)");
			return ;
		case V_NULL:
			buffer_append_string(buffer, "null");
			buffer_append_string(buffer, "(NULL)");
			return ;
		case V_OBJECT:
			append_json_obj_indent(buffer, (struct JsonObject*)ptr, indent+1);
			return ;
		case V_ARRAY:
			append_json_arr_indent(buffer, (struct JsonArray*)ptr, indent+1);
			return ;
		default:
			handle_error("JsonStringifyUtil error: Invalid value type.", 1);
	}
}

void print_json_obj(struct JsonObject *obj) {
	char *obj_str = stringify_json_obj(obj);
	printf("%s", obj_str);
	free(obj_str);
}

void print_json_arr(struct JsonArray *arr) {
	char *arr_str = stringify_json_arr(arr);
	printf("%s", arr_str);
	free(arr_str);
}

void print_json_obj_ent(struct JsonObject *obj, int index) {
	char *ent_str = stringify_json_obj_entry(obj, index);
	printf("%s", ent_str);
	free(ent_str);
}

char* stringify_json_obj(struct JsonObject *obj) {
	struct StringBuffer *buffer = init_StringBuffer(32);
	append_json_obj_indent(buffer, obj, 0);
	buffer_append_char(buffer, '\n');
	return stringify_string_buffer(buffer);
}

void check_newline_append(struct StringBuffer *buffer, enum JsonValueType type, int last_flag) {
	if (!last_flag) {
		buffer_append_char(buffer, ',');
	}
	buffer_append_char(buffer, '\n');
}

void append_json_obj_indent(struct StringBuffer *buffer, struct JsonObject *obj, int indent) {
	buffer_append_string(buffer, "{\n");
	for (int i = 0; i < obj->size; i++) {
		append_json_obj_entry_indent(buffer, obj, i, indent + 1);
		check_newline_append(buffer, obj->val_types[i], (i==(obj->size-1)));
	}
	append_indent(buffer, indent);
	buffer_append_char(buffer, '}');
}

char* stringify_json_arr(struct JsonArray *arr) {
	struct StringBuffer *buffer = init_StringBuffer(32);
	append_json_arr_indent(buffer, arr, 0);
	buffer_append_char(buffer, '\n');
	return stringify_string_buffer(buffer);
}

void append_json_arr_indent(struct StringBuffer *buffer, struct JsonArray *arr, int indent) {
	buffer_append_string(buffer, "[\n");
	for (int i = 0; i < arr->size; i++) {
		append_indent(buffer, indent+1);
		append_json_value(buffer, arr->elements[i], arr->types[i], indent);
		check_newline_append(buffer, arr->types[i], (i==(arr->size-1)));
	}
	append_indent(buffer, indent);
	buffer_append_char(buffer, ']');
}

char* stringify_json_obj_entry(struct JsonObject *obj, int index) {
	struct StringBuffer *buffer = init_StringBuffer(32);
	append_json_obj_entry_indent(buffer, obj, index, 0);
	buffer_append_char(buffer, '\n');
	return stringify_string_buffer(buffer);
}

void append_json_obj_entry_indent(struct StringBuffer *buffer, struct JsonObject *obj, int index, int indent) {
	append_indent(buffer, indent);
	buffer_append_string(buffer, obj->keys[index]);
	buffer_append_string(buffer, ": ");
	append_json_value(buffer, obj->vals[index], obj->val_types[index], indent);
}

