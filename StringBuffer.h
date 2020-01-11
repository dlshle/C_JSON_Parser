struct StringBuffer {
	char *string_buffer;
	int size;
	int cap;
};

struct StringBuffer* init_StringBuffer(int init_buffer_cap);
void buffer_append_string(struct StringBuffer *buffer, char *str);
void buffer_append_char(struct StringBuffer *buffer, char c);
void buffer_remove_interval(struct StringBuffer *buffer, int from, int len);
void buffer_remove_char_at(struct StringBuffer *buffer, int pos);
void free_buffer(struct StringBuffer *buffer);
void print_buffer(struct StringBuffer *buffer);
