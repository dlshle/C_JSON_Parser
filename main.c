#include <stdio.h>
#include <stdlib.h>
#include "JsonParser.h"

void test() {
	//char *json = "{\"num1\":123,\"num2\":0.1216,\"num3\":126,\"num4\":0.1e-12,\"num5\":1.2e+1,\"num6\":1.2e3,\"num7\":-12.31258e-158181, \"bol1\":false,\"NUl1\":null,\"str1\":\"asdwqccqIRJ(#(FHullnulltrue\", \"obj1\": {\"a\":123,\"b\":456}, \"arr1\": [{\"x\":1, \"y\":[1,2,3]}, [\"niu\", 123, \"bi!\", null], \"Asdsad\", true]}";
	char *json = "{\"problems\": [{\"Diabetes\":[{\"medications\":[{\"medicationsClasses\":[{\"className\":[{\"associatedDrug\":[{\"name\":\"asprin\",\"dose\":\"\",\"strength\":\"500 mg\"}],\"associatedDrug#2\":[{\"name\":\"somethingElse\",\"dose\":\"\",\"strength\":\"500 mg\"}]}],\"className2\":[{\"associatedDrug\":[{\"name\":\"asprin\",\"dose\":\"\",\"strength\":\"500 mg\"}],\"associatedDrug#2\":[{\"name\":\"somethingElse\",\"dose\":\"\",\"strength\":\"500 mg\"}]}]}]}],\"labs\":[{\"missing_field\": \"missing_value\"}]}],\"Asthma\":[{}]}]}";
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
	struct JsonObject *obj = parse_token_list(token_list);
	print_json_obj(obj);
	return 0;
}

struct JsonObject* parse_str(char mode, char* string) {
	struct JsonObject *obj = parse_json_str(string);
	if (mode == '0')
		print_json_obj(obj);
	return obj;
}

struct JsonObject* parse_file(char mode, char* path) {
	struct JsonObject *obj = parse_json_file(path);
	if (mode == '0')
		print_json_obj(obj);
	return obj;
}

// parser : run test
// parser 0 0 json_str : parse json string and print
// parser 1 0 json_file_path : parse json file and print
int main(int argc, char** argv) {
	//test();
	if (argc == 1) {
		test();
	} else if (argc == 4) {
		if (argv[1][0] == '0') {
			parse_str(argv[2][0], argv[3]);
		} else if (argv[1][0] == '1') {
			parse_file(argv[2][0], argv[3]);
		} else {
			handle_error("parse error: invalid second argument. (0 for parsing string, 1 for parsing file).", 1);
		}
	} else {
		handle_error("parse error: invalid number of arguments.\n parse mode print_flag string.", 1);
	}
	return 0;
}

