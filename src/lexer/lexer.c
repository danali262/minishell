#include "minishell.h"

static int	get_char_type_2(char c)
{
	if (c == '0')
		return (CHAR_NULL);
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
	else if (c == '&')
		return (CHAR_AMPERSAND);
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

static t_token	*loop(t_shell *prompt, t_token *token)
{
	t_counters	count;
	char		c;

	count.i = 0;
	count.j = 0;
	c = prompt->cmd[count.i];
	while (c != '\0')
	{
		c = prompt->cmd[count.i];
		prompt->chtype = get_char_type(prompt->cmd[count.i]);
		if (prompt->state == STATE_GENERAL)
			token = process_general_state(prompt, token, &count, c);
		else if (prompt->state == STATE_IN_DQUOTE)
			token = process_dquote_state(prompt, token, &count);
		else if (prompt->state == STATE_IN_QUOTE)
			token = process_quote_state(prompt, token, &count);
		count.i++;
	}
	return (token);
}

int	lexer_build(t_shell *prompt, t_lexer *lexerbuf)
{
	t_token	*token;

	if (lexerbuf == NULL)
		return (-1);
	if (prompt->size == 0)
	{
		lexerbuf->tokens_nbr = 0;
		return (0);
	}
	lexerbuf->tokens_list = malloc(sizeof(t_token));
	token = lexerbuf->tokens_list;
	tok_init(token, prompt->size);
	prompt->state = STATE_GENERAL;
	token = loop(prompt, token);
	token = lexerbuf->tokens_list;
	print_tokens(lexerbuf);
	return (0);
}
