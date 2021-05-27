#include "lexer.h"

t_token	*process_others(t_lexer_state *lex_state, t_token *token, t_counters
*count)
{
	if (count->j > 0)
	{			
		token->data[count->j] = 0;
		token->next = malloc(sizeof(t_token));
		if (!token->next)
			lexer_error(lex_state->tokens_list);
		token = token->next;
		tok_init(token, lex_state->line->size - count->i, lex_state);
		count->j = 0;
	}
	return (token);
}

t_token	*new_token(t_lexer_state *lex_state, t_token *token, t_counters *count)
{
	token->data[0] = lex_state->chtype;
	token->type = lex_state->chtype;
	token->next = malloc(sizeof(t_token));
	if (!token->next)
		lexer_error(lex_state->tokens_list);
	token = token->next;
	tok_init(token, lex_state->line->size - count->i, lex_state);
	return (token);
}
