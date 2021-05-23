#include "lexer.h"

void	tok_init(t_token *tok, int datasize)
{
	tok->data = malloc(datasize);
	tok->data[0] = 0;
	tok->next = NULL;
}

void	free_token(t_token *tok)
{
	if (tok->data)
		free(tok->data);
	free(tok);
}
