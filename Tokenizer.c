#include "Tokenizer.h"
#include "CharReader.h"
#include "ErrorHandler.h"
#include "StringBuffer.h"
#include <stdlib.h>
#include <stdio.h>
// TODO: use expect to error check json format
// construct token_list to store all TokenPairs detected from the json string
void tokenize() {
	token_list = init_token_list();
	do {
		list_add_pair(token_list, tokenize_token());
	} while(token_list->token_list[token_list->size-1]->type != END_DOCUMENT);
}

int is_whitespace(char c) {
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r');
}

int is_digit(char c) {
	return c >= '0' && c <= '9';
}

struct TokenPair* tokenize_token() {
	char c;
	while (1) {
		if (!has_more())
			return init_token_pair(END_DOCUMENT, NULL);
		c = next();
		if (!is_whitespace(c)) 
			break ;
	}
	switch (c) {
		case '{':
			return init_token_pair(BEGIN_OBJECT, "{");
		case '}':
			return init_token_pair(END_OBJECT, "}");
		case '[':
			return init_token_pair(BEGIN_ARRAY, "[");
		case ']':
			return init_token_pair(END_ARRAY, "]");
		case ':':
			return init_token_pair(SEP_COLON, ":");
		case ',':
			return init_token_pair(SEP_COMMA, ",");
		case 'n':
			return tokenize_null();
		case '"':
			return tokenize_string();
		case 't':
		case 'f':
			return tokenize_boolean();
		case '-':
			return tokenize_number();
	}
	if (is_digit(c))
		return tokenize_number();
	// tokenizer error: illegal character
	handle_error("Tokenizer error: illegal(unknown) character", 1);
}

struct TokenPair* tokenize_null() {
	if (!(next() == 'u' && next() == 'l' && next() == 'l'))
		handle_error("Tokenizer error: illegal character on tokenizing NULL.", 1);
	return init_token_pair(J_NULL, "null");
}

struct TokenPair* tokenize_boolean() {
	char c = peek();
	if (c == 't' && next() == 'r' && next() == 'u' && next() == 'e')
		return init_token_pair(BOOLEAN, "true");
	else if (c == 'f' && next() == 'a' && next() == 'l' && next() == 's' && next() == 'e')
		return init_token_pair(BOOLEAN, "false");
	else 
		handle_error("Tokenizer error: illegal character on tokenizing BOOLEAN.", 1);
}

int is_escape(char c) {
	return (c == '\\' || c == '"' || c == 'u' || c == 'n' || c == 'r' || c == 'b' || c == 't' || c == 'f');
}

int is_hex(char c) {
	// 0-9 && a-f && A-F
	return (c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F');
}


struct TokenPair* tokenize_string() {
	struct StringBuffer *buffer = init_StringBuffer(8);
	while (1) {
		char c = next();
		if (c == '\\') {
			// escape chars
			c = next();
			if (!is_escape(c)) 
				handle_error("Tokenizer error: illegal character on tokenizing string(illegal escape character).", 1);
			buffer_append_char(buffer, '\\');
			buffer_append_char(buffer, c);
			if (c == 'u') {
				// unicode handling(4 chars)
				for (int i = 0; i < 4; i++) {
					c = next();
					if (!is_hex(c))
						handle_error("Tokenizer error: illegal character on tokenizing string(illegal length after \\u).", 1);
					buffer_append_char(buffer, c);
				}
			}
		} else if (c == '\r' || c == '\n') {
			// no newline is allowed in string
			handle_error("Tokenizer error: illegal character on tokenizing string(newline character in string).", 1);
		} else if (c == '"') {
			// close string
			struct TokenPair *pair = init_token_pair(STRING, buffer->string_buffer);
			// only free buffer, free string_buffer later
			free(buffer);
			return pair;
		} else {
			buffer_append_char(buffer, c);
		}
	}
}

void read_digits(struct StringBuffer *buffer) {
	while (is_digit(next()))
		buffer_append_char(buffer, peek());
	// back one char, so that next() will return the next non-digit char
	back();
}

// use after e is detected(peek() == 'e')
void read_exp(struct StringBuffer *buffer) {
	buffer_append_char(buffer, 'e');
	char c = next();
	// exp could be 123e+123 123e123 123e-123
	if (c == '+' || c == '-' || is_digit(c))
		buffer_append_char(buffer, c);
	else 
		handle_error("Tokenizer error: illegal character on tokenizing number(illegal character detected after possible exp section).", 1);
	read_digits(buffer);
}

// use after . is detected(peek() == '.')
void read_frac(struct StringBuffer *buffer) {
	buffer_append_char(buffer, '.');
	read_digits(buffer);
	if (next() == 'e') {
		read_exp(buffer);
	} else {
		back();
	}
}

struct TokenPair* tokenize_number() {
	// (-) 0.xxxx xxx.xxx (xxx).xxxe(+|-)xxx 0exxx
	struct StringBuffer *buffer = init_StringBuffer(8);
	char c = peek();
	int frac_flag = 0;
	int exp_flag = 0;
	int finish = 0;
	if (c == '-') {
		buffer_append_char(buffer, c);
		c = next();
		if (!is_digit(c))
			handle_error("Tokenizer error: illegal character on tokenizing number(non-digit character detected at digit section).", 1);
	}
	// append the 1st digit
	buffer_append_char(buffer, c);
	// assume c = 1st #
	if (c == '0') {
		// only 0.xxx(e)(+|-)xx is allowed
		c = next();
		if (c == 'e') {
			// 0exxx
			read_exp(buffer);
		} else if (c == '.') {
			// only 1 fraction is allowed
			frac_flag = 1;
			read_frac(buffer);
		} else {
			// only 0 is allowed if not a fraction
			finish = 1;
			back();
		}
	}
	// after special cases
	if (!finish) {
		read_digits(buffer);
		c = next();
		if (c == '.') {
			if (frac_flag)
				handle_error("Tokenizer error: illegal character on tokenizing number(two fraction(.) detected).", 1);
			read_frac(buffer);
		} else if (c == 'e') {
			read_exp(buffer);
		} else {
			back();
		}
	}
	struct TokenPair *pair = init_token_pair(NUMBER,buffer->string_buffer);
	free(buffer);
	return pair;
}
