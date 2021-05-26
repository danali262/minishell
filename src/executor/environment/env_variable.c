#include "../executor.h"

#include "libft.h"

char    *replace_dollar_question(t_treenode *arg_node, t_shell *shell)
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

char    *get_envar_value(char *command, t_shell *shell)
{
	t_envlist	*envar_node;
	char	*value;

	envar_node = shell->env_list;
	value = NULL;
	while (envar_node->next != NULL)
	{
		if (ft_strncmp(envar_node->name, command, ft_strlen(command)) == 0)
		{
			value = envar_node->value;
			break ;
		}
		envar_node = envar_node->next;
	}
	return (value);
}

int	is_envar(t_treenode *arg_node)
{
	if (arg_node->data[0] == '$' && arg_node->left == NULL)
		return (1);
	return (0);
}

char    *replace_envar(t_treenode *arg_node, t_shell *shell)
{
	char	*value;

	value = NULL;
	if (arg_node->data[1] == '?')
		value = replace_dollar_question(arg_node, shell);
	else
		value = get_envar_value(arg_node->data + 1, shell);
	return (value);
}