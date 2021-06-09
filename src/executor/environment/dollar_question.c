#include "../executor.h"

#include "libft.h"

char	*replace_dollar_question(t_treenode *arg_node, t_shell *shell)
{
	char	*value;
	char	*exit_code_str;
	size_t	data_len;

	value = NULL;
	exit_code_str = ft_itoa(shell->exit_code);
	data_len = ft_strlen(arg_node->data);
	if (data_len == 2)
		value = exit_code_str;
	else
	{
		value = ft_strjoin(exit_code_str, arg_node->data + 2);
		free(exit_code_str);
	}
	return (value);
}
