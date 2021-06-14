#include "parser.h"

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
