#include "minishell.h"
#include <glob.h>

void    tok_init(t_token *tok, int datasize)
{
    tok->data = malloc(datasize);	/* doesn't that leak memory? we allocate more than we need sometimes..  */
    tok->data[0] = 0;
    tok->type = CHAR_NULL;
    tok->next = NULL;
}

int		get_char_type(char c)
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
	else if (c == '0')
		return (CHAR_NULL);
	else
		return (CHAR_GENERAL);
}

void	strip_quotes(char *src, char *dest)
{
	int		n;
	int		i;
	char	lastquote;
	int		j;
	char	c;

	n = ft_strlen(src);
	if (n <= 1)
	{
		ft_strlcpy(dest, src, ft_strlen(src));
		return ;
	}
	lastquote = 0;
	j = 0;
	i = 0;
	while (i < n)
	{
		c = src[i];
		if ((c == '\'' || c == '\"') && lastquote == 0)
			lastquote = c;
		else if (c == lastquote)
			lastquote = 0;
		else
			dest[j++] = c;
		i++;
	}
	dest[j] = 0;
}

int		lexer_build(char *input, size_t size, t_lexer *lexerbuf)
{
    t_token     *token;
    size_t      i;
	int			j;
	int			ntemptok;
	char		c;
	int			state;
	int			chtype;

    if (lexerbuf == NULL)
        return(-1);
    if (size == 0)
    {
        lexerbuf->tokens_nbr = 0;
        return (0);
    }
    lexerbuf->tokens_list = malloc(sizeof(t_token));

    token = lexerbuf->tokens_list;  /* allocate the first token */
    tok_init(token, size);

	i = 0;
	j = 0;
	ntemptok = 0;
	state = STATE_GENERAL;
	c = input[i];	/* what happens if input is c == '\0' */
	while (c != '\0')	/* need to make sure that this is executed at least once */
	{
		c = input[i];
		chtype = get_char_type(c);
		if (state == STATE_GENERAL)
		{
			if (chtype == CHAR_QUOTE)
			{
				state = STATE_IN_QUOTE;
				token->data[j++] = CHAR_QUOTE;
				token->type = TOKEN;
			}
			else if (chtype == CHAR_DQUOTE)
			{
				state = STATE_IN_DQUOTE;
				token->data[j++] = CHAR_DQUOTE;
				token->type = TOKEN;
			}
			else if (chtype == CHAR_ESCAPESEQUENCE)
			{
				token->data[j++] = input[++i];
				token->type = TOKEN;
			}
			else if (chtype == CHAR_GENERAL)
			{
				// printf("j before is %d\n", j);
				token->data[j++] = c;
				// printf("j after is %d\n", j);
				token->type = TOKEN;
			}
			else if (chtype == CHAR_WHITESPACE)
			{
				if (j > 0)
				{
					token->data[j] = 0;	/* does that null terminate the token? */
					token->next = malloc(sizeof(t_token)); /* because it means that another token is coming up? */
					token = token->next;
					tok_init(token, size - i);
					j = 0;
				}
			}
			else if (chtype == CHAR_SEMICOLON | chtype == CHAR_GREATER | chtype == CHAR_LESSER | chtype == CHAR_AMPERSAND | chtype == CHAR_PIPE)
			{
				if (j > 0)	/* end the token that was being read before */
				{
					token->data[j] = 0;
					token->next = malloc(sizeof(t_token));
					token = token->next;
					tok_init(token, size - i);
					j = 0;
				}
				token->data[0] = chtype;
				token->data[1] = 0;
				token->type = chtype;
				token->next = malloc(sizeof(t_token));
				token = token->next;
				tok_init(token, size - i);
			}
		}
		else if (state == STATE_IN_DQUOTE)
		{
			token->data[j++] = c;
			if (chtype == CHAR_DQUOTE)
				state = STATE_GENERAL;
		}
		else if (state == STATE_IN_QUOTE)
		{
			token->data[j++] = c;
			if (chtype == CHAR_QUOTE)
				state = STATE_GENERAL;
		}
		if (chtype == CHAR_NULL)		/* try to understand the use of this one */
		{
			if (j > 0)
			{
				token->data[j] = 0;
				ntemptok++;		/* what is this for? */
				j = 0;
			}
		}
		i++;
	}
	return (0);
}
