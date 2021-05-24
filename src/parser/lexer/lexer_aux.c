#include "lexer.h"

int	tok_init(t_token *tok, int datasize, t_lexer_state *lex_state)
{
	tok->data = malloc(datasize);
	if (!tok->data)
		return (-1);
	tok->data[0] = 0;
	tok->type = 0;
	tok->next = NULL;
	lex_state->tokens_nbr++;
	return (0);
}

void	free_token(t_token *tok)
{
	if (tok->data)
		free(tok->data);
	free(tok);
}
