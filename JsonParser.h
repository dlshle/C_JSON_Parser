#ifndef __JSON_PARSER_H__
#define __JSON_PARSER_H__

#include "CharReader.h"
#include "StringBuffer.h"
#include "Tokenizer.h"
#include "Parser.h"

struct JsonObject* parse_json_str(char *json_str);
struct JsonObject* parse_json_file(char *path);

#endif
