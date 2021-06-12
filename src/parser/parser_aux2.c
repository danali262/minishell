#include "parser.h"

#include <stdbool.h>



char	*strip_quotes(char *arg, t_treenode *node)
{
	size_t	token_len;
	char	*temp;
	char	quote;
	int		i;
	int		j;
	int		between_quotes_len;
	bool	is_quote_found;
	
	token_len = ft_strlen(arg);
	temp = ft_calloc(token_len + 1, sizeof(char);)
	if (!temp)
		parser_error(node);
	i = 0;
	j = 0;
	between_quotes_len = 0;
	is_quote_found = false;
	while (arg[i] != '\0')
	{
		if (arg[i] == '\'' || arg[i] == '"')
		{
			is_quote_found = true;
			quote = arg[i];
			pairing_quote_pos = ft_strchr(arg + i + 1, quote);
			if (pairing_quote_pos != NULL)
			{
				between_quotes_len = pairing_quote_pos - arg + i - 1;
				ft_memcpy(temp + j, arg + i + 1, between_quotes_len);
				i += between_quotes + 2;
				j += between_quotes;
			}
			else
			{
				ft_memcpy(temp + j, arg + i, token_len + 1 - i);
				break ;
			}
		}
	}
	if (is_quote_found == false)
	{
		free(temp);
		return (arg);
	}
	free(arg);
	return (temp);
}

char	*create_arg(char *arg, t_treenode *node)
{
	char	*temp;
	int		arg_len;
	int		i;
	int		j;

	arg_len = ft_strlen(arg);
	temp = malloc(sizeof(char) * (arg_len - 1));
	if (!temp)
		parser_error(node);
	i = 2;
	j = 0;
	while (j < arg_len - 2)
	{
		temp[j] = arg[i];
		i++;
		j++;
	}
	temp[i] = '\0';
	return (temp);
}
