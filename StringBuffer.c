#include "StringBuffer.h"
#include "ErrorHandler.h"
#include <stdlib.h>
#include <stdio.h>

#define EXPAND_FACTOR 1.5

void check_buffer_nullity(struct StringBuffer *buffer) {
	if (buffer == NULL)
		handle_error("StringBuffer error: NULL buffer.", 1);
}

void expand_detect(struct StringBuffer *buffer) {
	if (buffer->size >= buffer->cap) {
		expand_buffer(buffer);
	}
}

int expand_buffer(struct StringBuffer *buffer) {
	check_buffer_nullity(buffer);
	buffer->string_buffer = realloc(buffer->string_buffer, buffer->cap * sizeof(char) * EXPAND_FACTOR);
	return buffer->string_buffer != NULL;
}

struct StringBuffer* init_StringBuffer(int init_buffer_cap) {
	struct StringBuffer *buffer = malloc(sizeof(struct StringBuffer));
	if (buffer == NULL)
		handle_error("StringBuffer error: buffer initialization failed.", 1);
	buffer->string_buffer = malloc(sizeof(char) * init_buffer_cap);
	if (buffer->string_buffer == NULL)
		handle_error("StringBuffer error: buffer initialization failed.", 1);
	buffer->size = 0;
	buffer->cap = init_buffer_cap;
	return buffer;
}

void buffer_append_string(struct StringBuffer *buffer, char *str) {
	check_buffer_nullity(buffer);
	if (str[0] == '\0')
		return ;
	int len = 0;
	while (str[len] != '\0') {
		buffer_append_char(buffer, str[len++]);
	}
}

void buffer_append_char(struct StringBuffer *buffer, char c) {
	check_buffer_nullity(buffer);
	expand_detect(buffer);
	buffer->string_buffer[buffer->size++] = c;
}

// shift from $from to the left by $by(exclusive)
void buffer_shift_from_by(struct StringBuffer *buffer, int from, int by) {
	check_buffer_nullity(buffer);
	if (from > buffer->size)
		handle_error("StringBuffer error: invalid shift param(from > buffer size)", 1);
	if (by > from)
		handle_error("StringBuffer error: invalid shift param(by < from).", 1);
	for (int i = from - by; i < buffer->size; i++) {
		buffer->string_buffer[i] = buffer->string_buffer[i + by];
	}
}

// remove interval from $from to $to(exclusive)
void buffer_remove_interval(struct StringBuffer *buffer, int from, int len) {
	check_buffer_nullity(buffer);
	buffer_shift_from_by(buffer, from + len, len);
}

void buffer_remove_char_at(struct StringBuffer *buffer, int pos) {
	check_buffer_nullity(buffer);
	buffer_shift_from_by(buffer, pos+1, 1);
}

void free_buffer(struct StringBuffer *buffer) {
	check_buffer_nullity(buffer);
	free(buffer->string_buffer);
	free(buffer);
}

void print_buffer(struct StringBuffer *buffer) {
	check_buffer_nullity(buffer);
	for (int i = 0; i < buffer->size; i++) {
		printf("%c", buffer->string_buffer[i]);
	}
}
