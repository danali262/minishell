#include "lexer.h"

int	tok_init(t_token *tok, int datasize, t_lexer_state *lex_state)
{
	if (datasize < 1)
		datasize = 1;
	tok->data = ft_calloc(datasize + 1, sizeof(char));
	if (!tok->data)
		return (-1);
	tok->data[0] = '\0';
	tok->type = CHAR_EMPTY;
	tok->next = NULL;
	lex_state->tokens_nbr++;
	return (0);
}

void	free_token(t_token *tok)
{
	if (tok->data)
	{
		free(tok->data);
		tok->data = NULL;
	}
	tok->type = CHAR_EMPTY;
	free(tok);
	tok = NULL;
}

static void	tok_destroy(t_token *token)
{
	if (token != NULL)
	{
		free(token->data);
		token->data = NULL;
		token->type = CHAR_EMPTY;
		tok_destroy(token->next);
		free(token);
		token = NULL;
	}
}

void	lexer_destroy(t_lexer_state *lex_state)
{
	if (lex_state == NULL)
		return ;
	tok_destroy(lex_state->tokens_list);
}
