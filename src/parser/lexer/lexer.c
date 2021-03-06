#include "lexer.h"
#include "../../reader/read_command_line.h"

static int	get_char_type_2(char c)
{
	if (c == '\0')
		return (CHAR_EMPTY);
	else
		return (CHAR_GENERAL);
}

static int	get_char_type(char c)
{
	if (c == '\'')
		return (CHAR_QUOTE);
	else if (c == '\"')
		return (CHAR_DQUOTE);
	else if (c == '|')
		return (CHAR_PIPE);
	else if (c == ' ')
		return (CHAR_WHITESPACE);
	else if (c == ';')
		return (CHAR_SEMICOLON);
	else if (c == '\\')
		return (CHAR_ESCAPESEQUENCE);
	else if (c == '\t')
		return (CHAR_TAB);
	else if (c == '\n')
		return (CHAR_NEWLINE);
	else if (c == '>')
		return (CHAR_GREATER);
	else if (c == '<')
		return (CHAR_LESSER);
	else
		return (get_char_type_2(c));
}

static t_token	*loop(t_lexer_state *lex_state, t_token *token)
{
	t_counters	count;
	char		c;

	count.i = 0;
	count.j = 0;
	while (lex_state->line->buf[count.i] == ' ')
		count.i++;
	c = lex_state->line->buf[count.i];
	while (c != '\0')
	{
		c = lex_state->line->buf[count.i];
		lex_state->chtype = get_char_type(lex_state->line->buf[count.i]);
		if (lex_state->state == STATE_GENERAL)
			token = process_general_state(lex_state, token, &count, c);
		else if (lex_state->state == STATE_IN_DQUOTE)
			token = process_dquote_state(lex_state, token, &count);
		else if (lex_state->state == STATE_IN_QUOTE)
			token = process_quote_state(lex_state, token, &count);
		count.i++;
	}
	return (token);
}

int	lexer_build(t_lexer_state *lex_state)
{
	t_token	*token;

	if (lex_state->line->size == 0)
	{
		lex_state->tokens_nbr = 0;
		return (0);
	}
	lex_state->tokens_nbr = 0;
	lex_state->tokens_list = ft_calloc(1, sizeof(t_token));
	if (!lex_state->tokens_list)
		return (-1);
	token = lex_state->tokens_list;
	if (tok_init(token, lex_state->line->size, lex_state) == -1)
		return (-1);
	lex_state->state = STATE_GENERAL;
	lex_state->tokens_nbr = 0;
	token = loop(lex_state, token);
	token = lex_state->tokens_list;
	clear_command_line(lex_state->line);
	return (1);
}
