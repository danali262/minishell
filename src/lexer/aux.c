#include "lexer.h"

void	tok_init(t_token *tok, int datasize)
{
	tok->data = malloc(datasize);
	tok->data[0] = 0;
	tok->type = CHAR_NULL;
	tok->next = NULL;
}
