#!/bin/sh
gcc ErrorHandler.c TokenTypes.c TokenList.c StringBuffer.c CharReader.c Tokenizer.c main.c -ggdb -o parser
