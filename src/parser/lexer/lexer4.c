#include "lexer.h"

t_token	*process_dquote_state(t_lexer_state *lex_state, t_token *token,
t_counters *count)
{
	token->data[count->j++] = lex_state->line->buf[count->i];
	if (lex_state->chtype == CHAR_DQUOTE)
		lex_state->state = STATE_GENERAL;
	if (lex_state->chtype == CHAR_EMPTY)
	{
		token = process_others(lex_state, token, count);
		token = new_token(lex_state, token, count);
	}
	return (token);
}

t_token	*process_quote_state(t_lexer_state *lex_state, t_token *token,
t_counters *count)
{
	token->data[count->j++] = lex_state->line->buf[count->i];
	if (lex_state->chtype == CHAR_QUOTE)
		lex_state->state = STATE_GENERAL;
	if (lex_state->chtype == CHAR_EMPTY)
	{
		token = process_others(lex_state, token, count);
		token = new_token(lex_state, token, count);
	}
	return (token);
}
