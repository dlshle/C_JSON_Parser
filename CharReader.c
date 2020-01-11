#include "CharReader.h"

void init_reader(char *str_json) {
	pos = 0;
	size = 0;
	while (str_json[size++] != 0);
	size--;
	json_str = str_json;
}

char peek() {
	if (size == 0)
		return -1;
	if (pos - 1 >= size)
		return -1;
	return json_str[max(0, pos-1)];
}

char next() {
	if (pos >= size)
		return -1;
	return json_str[pos++];
}

char back() {
	if (size == 0)
		return -1;
	pos = max(0, --pos);
	return json_str[pos];
}

int has_more() {
	return pos < size;
}

int max(int a, int b) {
	return a>b?a:b;
}
