#include "parser.h"

bool	term(int tokentype, char **buffer, t_curtok *curtok, t_treenode *node)
{
	if (curtok->current_token == NULL)
		return (false);
	if ((curtok->current_token->type == tokentype) || (tokentype == CHAR_REDIR
			&& (curtok->current_token->type == CHAR_GREATER
				|| curtok->current_token->type == CHAR_LESSER
				|| curtok->current_token->type == CHAR_APPEND
				|| curtok->current_token->type == CHAR_RHOMBUS)))
	{
		if (buffer != NULL)
		{
			*buffer = malloc(ft_strlen(curtok->current_token->data) + 1);
			if (!*buffer)
				parser_error(node);
			ft_strlcpy(*buffer, curtok->current_token->data,
				ft_strlen(curtok->current_token->data) + 1);
		}
		curtok->current_token = curtok->current_token->next;
		return (true);
	}
	curtok->current_token = curtok->current_token->next;
	return (false);
}

int	handle_vars_and_args(char *arg)
{
	size_t	arg_len;
	int		i;

	arg_len = ft_strlen(arg);
	i = 0;
	if (arg[i] == '\'' && arg[arg_len - 1] == '\'')
		return (0);
	else
	{
		if (arg[i] == '\"')
		{
			i++;
			arg_len -= 2;
		}
		if (arg[i] == '$')
		{
			i++;
			if (arg[i] == '?' && arg_len != 2)
				return (2);
			else
				return (1);
		}
		else
			return (0);
	}
}

char	*create_arg(char *arg, t_treenode *node)
{
	char	*temp;
	size_t	arg_len;
	int		i;
	size_t	j;

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
