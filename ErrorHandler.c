#include <stdlib.h>
#include <stdio.h>
#include "ErrorHandler.h"

void handle_error(char *msg, int exit_on_error) {
	fprintf(stderr, "%s\n", msg);
	if (exit_on_error)
		exit(1);
}
