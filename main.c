#include <stdio.h>
#include <stdlib.h>
#include "CharReader.h"
#include "StringBuffer.h"
#include "Tokenizer.h"

int main(int argc, char** argv) {
	char *json = "{\"num1\":123,\"num2\":0.1216,\"num3\":126,\"num4\":0.1e-12,\"num5\":1.2e+1,\"num6\":1.2e3,\"num7\":-12.31258e-158181, \"bol1\":false,\"NUl1\":null,\"str1\":\"asdwqccqIRJ(#(FHullnulltrue\", \"obj1\": {\"a\":123,\"b\":456}, \"arr1\": [{\"x\":1, \"y\":[1,2,3]}, [\"niu\", 123, \"bi!\", null], \"Asdsad\", true]}";
	printf("%s\n", json);
	init_reader(json);
	/*
	while (has_more()) {
		printf("%c", next());
	}
	printf("\n");
	struct TokenList *list = init_token_list();
	for (int i = 0; i < 20; i++) {
		list_add_pair(list, init_token_pair(NUMBER, "123"));
	}
	//list_print(list);
	int count = 0;
	while (list_has_more(list)) {
		printf("%d of %d:", count++, list->size);
		print_token_pair(list_next_pair(list));
	}
	*/
	tokenize();
	list_print(token_list);
	/*
	struct StringBuffer *buffer = init_StringBuffer(10);
	buffer_append_string(buffer, "What the fuck!!!\n");
	print_buffer(buffer);
	buffer_remove_interval(buffer, 1, 3);
	buffer_append_string(buffer, "asd\n");
	buffer_append_char(buffer, 'x');
	buffer_remove_char_at(buffer, buffer->size-1);
	print_buffer(buffer);
	*/
	return 0;
}
