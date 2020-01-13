#!/bin/sh
gcc JsonParser.c ErrorHandler.c JsonObject.c JsonArray.c JsonStringifyUtil.c Parser.c TokenTypes.c TokenList.c StringBuffer.c CharReader.c Tokenizer.c main.c -ggdb -o parser
