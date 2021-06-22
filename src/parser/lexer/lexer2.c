#include "lexer.h"

static t_token	*process_quote(t_lexer_state *lex_state, t_token *token,
t_counters *count)
{
	lex_state->state = STATE_IN_QUOTE;
	token->data[count->j++] = CHAR_QUOTE;
	token->type = TOKEN;
	return (token);
}

static t_token	*process_dquote(t_lexer_state *lex_state, t_token *token,
t_counters *count)
{
	lex_state->state = STATE_IN_DQUOTE;
	token->data[count->j++] = CHAR_DQUOTE;
	token->type = TOKEN;
	return (token);
}

static t_token	*process_general(t_token *token, t_counters *count, char c)
{
	token->data[count->j++] = c;
	token->type = TOKEN;
	return (token);
}

t_token	*process_general_state(t_lexer_state *lex_state, t_token *token,
t_counters *count, char c)
{
	if (lex_state->chtype == CHAR_QUOTE)
		token = process_quote(lex_state, token, count);
	else if (lex_state->chtype == CHAR_DQUOTE)
		token = process_dquote(lex_state, token, count);
	else if (lex_state->chtype == CHAR_ESCAPESEQUENCE)
	{
		token->data[count->j++] = lex_state->line->buf[++count->i];
		token->type = TOKEN;
	}
	else if (lex_state->chtype == CHAR_GENERAL)
		token = process_general(token, count, c);
	else if ((lex_state->chtype == CHAR_SEMICOLON) | (lex_state->chtype
			== CHAR_GREATER) | (lex_state->chtype == CHAR_LESSER)
		| (lex_state->chtype == CHAR_EMPTY) | (lex_state->chtype == CHAR_PIPE) || (lex_state->chtype == CHAR_WHITESPACE))
	{
		token = process_others(lex_state, token, count);
		token = new_token(lex_state, token, count);
	}
	return (token);
}
