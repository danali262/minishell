#include "minishell.h"
#include <glob.h>

void    tok_init(t_token *tok, int datasize)
{
    tok->data = malloc(datasize + 1);	/* I am a bit confused with that as well */
    tok->data[0] = 0;			/* why we do that? */
    tok->type = CHAR_NULL;
    tok->next = NULL;			/* why we do that? */
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
	t_token		*saved;	
    size_t      i;
	int			j;
	int			ntemptok;
	char		c;
	int			state;
	int			chtype;
	int			k;
	glob_t		globbuf;
	char		*stripped;

    if (lexerbuf == NULL)
        return(-1);
    if (size == 0)
    {
        lexerbuf->tokens_nbr = 0;
        return (0);
    }
    lexerbuf->tokens_list = malloc(sizeof(t_token));

    token = lexerbuf->tokens_list;  /* allocate the first token */
    tok_init(token, size);          /* we use the size of the whole command though...? */

	i = 0;
	j = 0;
	ntemptok = 0;
	state = STATE_GENERAL;
	do	/* we use do... while so that the content is executed at least once */
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
				token->data[j++] = c;
				token->type = TOKEN;
			}
			else if (chtype == CHAR_WHITESPACE)
			{
				if (j > 0)
				{
					token->data[j] = 0;	/* zeroes in the tokens represent whitespaces? */
					token->next = malloc(sizeof(t_token)); /* because it means that another token is coming up? */
					token = token->next;
					tok_init(token, size - i);
					j = 0;
				}
			}
			else if(CHAR_SEMICOLON | CHAR_GREATER | CHAR_LESSER | CHAR_AMPERSAND | CHAR_PIPE)
			{
				if (j > 0)	/* end the token that was being read before */
				{
					token->data[j] = 0;
					token->next = malloc(sizeof(t_token));
					token = token->next;
					tok_init(token, size - i);
					j = 0;
				}
				token->data[0] = chtype;	/* next token */
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
		if (chtype == CHAR_NULL)
		{
			if (j > 0)
			{
				token->data[j] = 0;
				ntemptok++;		/* what is this for? */
				j = 0;
			}
		}
		i++;
	}	while (c != '\0');
	token = lexerbuf->tokens_list;
	k = 0;
	while (token != NULL)
	{
		if (token->type == TOKEN)
		{
			glob(token->data, GLOB_TILDE, NULL, &globbuf);	/*  */
			if (globbuf.gl_pathc > 0)
			{
				k += globbuf.gl_pathc;
				saved = token->next;	/* save the next token so we can attach it later */
				free(token->data);		/* replace the current token with the first one */
				token->data = malloc(ft_strlen(globbuf.gl_pathv[0]) + 1);
				ft_strlcpy(token->data, globbuf.gl_pathv[0], ft_strlen(globbuf.gl_pathv[0] + 1));

				i = 1;
				while (i < globbuf.gl_pathc)
				{
					token->next = malloc(sizeof(t_token));
					tok_init(token->next, ft_strlen(globbuf.gl_pathv[i]));
					token = token->next;
					token->type = TOKEN;
					ft_strlcpy(token->data, globbuf.gl_pathv[i], ft_strlen(globbuf.gl_pathv[i]));
					i++;
				}
				token->next = saved;
			}
			else	/* token from the user might be inside quotation  to escape special characters, hence strip the quotation symbol */
			{
				stripped = malloc(ft_strlen(token->data) + 1);
				strip_quotes(token->data, stripped);
				free(token->data);
				token->data = stripped;
				k++;
			}
		}
		token = token->next;
	}
	lexerbuf->tokens_nbr = k;
	return (k);
}
