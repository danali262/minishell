#include "lexer.h"

static t_token	*process_quote(t_shell *prompt, t_token *token, t_counters
*count)
{
	prompt->state = STATE_IN_QUOTE;
	token->data[count->j++] = CHAR_QUOTE;
	token->type = TOKEN;
	return (token);
}

static t_token	*process_dquote(t_shell *prompt, t_token *token, t_counters
*count)
{
	prompt->state = STATE_IN_DQUOTE;
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

static t_token	*process_whitespace(t_shell *prompt, t_token *token,
t_counters *count)
{
	if (count->j > 0)
	{
		token->data[count->j] = 0;
		token->next = malloc(sizeof(t_token));
		token = token->next;
		tok_init(token, prompt->size - count->i);
		count->j = 0;
	}
	return (token);
}

t_token	*process_general_state(t_shell *prompt, t_token *token, t_counters
*count, char c)
{
	if (prompt->chtype == CHAR_QUOTE)
		token = process_quote(prompt, token, count);
	else if (prompt->chtype == CHAR_DQUOTE)
		token = process_dquote(prompt, token, count);
	else if (prompt->chtype == CHAR_ESCAPESEQUENCE)
	{
		token->data[count->j++] = prompt->cmd[++count->i];
		token->type = TOKEN;
	}
	else if (prompt->chtype == CHAR_GENERAL)
		token = process_general(token, count, c);
	else if (prompt->chtype == CHAR_WHITESPACE)
		token = process_whitespace(prompt, token, count);
	else if ((prompt->chtype == CHAR_SEMICOLON) | (prompt->chtype
			== CHAR_GREATER) | (prompt->chtype == CHAR_LESSER) | (prompt->chtype
			== CHAR_AMPERSAND)
		| (prompt->chtype == CHAR_PIPE))
	{
		token = process_others(prompt, token, count);
		token = new_token(prompt, token, count);
	}
	return (token);
}
