#ifndef __CHAR_READER_H__
#define __CHAR_READER_H__
char *json_str;
unsigned int pos;
unsigned int size;

void init_reader(char *str_json);
char peek();
char next();
char back();
int has_more();
int max(int a, int b);
#endif
