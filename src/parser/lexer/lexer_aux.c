#include "lexer.h"

void	tok_init(t_token *tok, int datasize)
{
	tok->data = malloc(datasize);
	tok->data[0] = 0;
	tok->next = NULL;
}

void	free_token(t_token *tok)
{
	if (tok->data)
		free(tok->data);
	free(tok);
}

static void	token_strip_quotes(t_token *current_token)
{
	int		i;
	int		token_len;
	char	*temp;
	int		temp_len;

	token_len = ft_strlen(current_token->data);
	temp_len = token_len - 2;
	temp = malloc(sizeof(char) * (temp_len + 1));
	i = 0;
	if ((current_token->data[i] == '\''&& current_token->data[token_len - 1] == '\'') || (current_token->data[i] == '\"' && current_token->data[token_len - 1] == '\"'))
	{
		while (i < temp_len)
		{
			temp[i] = current_token->data[i + 1];
			i++;
		}
		temp[i] = '\0';
		free(current_token->data);
		current_token->data = ft_strdup(temp);
	}
}

void	strip_quotes(t_lexer *lexerbuf)
{
	t_token *current_token;

	current_token = lexerbuf->tokens_list;
	while (current_token != NULL)
	{
		token_strip_quotes(current_token);
		current_token = current_token->next;
	}
}