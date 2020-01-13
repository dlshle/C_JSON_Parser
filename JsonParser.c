#include <stdio.h>
#include <stdlib.h>
#include "JsonParser.h"

// file helper functions
char* read_file(char *path) {
	FILE *fp;  
    if(NULL == (fp = fopen(path, "r")))  
    {  
		handle_error("JsonParser error: unable to open json file.", 1);
    }  
  
	struct StringBuffer *buffer = init_StringBuffer(64);
    char ch;  
    while(EOF != (ch=fgetc(fp)))  
    {  
		buffer_append_char(buffer, ch);
    }  
  	// fclose(fp);
	char *json_str = buffer->string_buffer;
	free(buffer);
	return json_str;
}

struct JsonObject* parse_json_str(char *json_str) {
	init_reader(json_str);
	tokenize();
	return parse_token_list(token_list);
}

struct JsonObject* parse_json_file(char *path) {
	return parse_json_str(read_file(path));
}
