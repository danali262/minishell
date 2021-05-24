#include "parser.h"

char	*strip_quotes(char *arg, t_treenode *node)
{
	int		i;
	int		token_len;
	char	*temp;
	int		temp_len;

	token_len = ft_strlen(arg);
	temp_len = token_len - 2;
	temp = malloc(sizeof(char) * (temp_len + 1));
	if (!temp)
		parser_error(node);
	i = 0;
	if ((arg[i] == '\'' && arg[token_len - 1] == '\'') || (arg[i] == '\"'
			&& arg[token_len - 1] == '\"'))
	{
		while (i < temp_len)
		{
			temp[i] = arg[i + 1];
			i++;
		}
		temp[i] = '\0';
		free(arg);
		arg = ft_strdup(temp);
		free(temp);
	}
	return (arg);
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
