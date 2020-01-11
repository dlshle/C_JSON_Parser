enum TokenType {
	BEGIN_OBJECT = 1,
    END_OBJECT = 2,
    BEGIN_ARRAY = 4,
    END_ARRAY = 8,
    J_NULL = 16,
    NUMBER = 32,
    STRING = 64,
    BOOLEAN = 128,
    SEP_COLON = 256,
    SEP_COMMA = 512,
    END_DOCUMENT = 1024
};

struct TokenPair {
	enum TokenType type;
	char *value;
};

struct TokenPair* init_token_pair(enum TokenType type, char *value);

void free_token_pair(struct TokenPair *pair, int free_val);

char* get_token_type_str(enum TokenType type);

void print_token_pair(struct TokenPair *pair);
