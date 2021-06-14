#include "builtins.h"
#include "../executor.h"

#include "libft.h"

int	execute_export(t_treenode *simple_cmd_node, t_shell *shell)
{
	t_treenode	*arg_node;
	char		*envar_name;
	char		*value_start;

	value_start = NULL;
	if (simple_cmd_node->left == NULL)
		execute_env(simple_cmd_node, shell);
	else
	{
		arg_node = simple_cmd_node->left;
		while (arg_node != NULL)
		{
			arg_node->data = check_envars_and_quotes(arg_node, shell);
			if (arg_node->data == NULL)
				return (ERROR);
			envar_name = get_envar_name(arg_node->data);
			if (envar_name == NULL)
				return (ERROR);
			if (ft_strcmp(envar_name, arg_node->data) != 0)
			{
				value_start = arg_node->data + ft_strlen(envar_name) + 1;
				if (update_env_list(shell, envar_name, value_start) == ERROR)
					return (ERROR);
			}
			arg_node = arg_node->left;
		}
	}
	return (SUCCESS);
}

int	execute_unset(t_treenode *simple_cmd_node, t_shell *shell)
{
	t_treenode	*arg_node;
	t_envlist	*envar_node;
	t_envlist	*temp;

	if (simple_cmd_node->left != NULL)
	{
		arg_node = simple_cmd_node->left;
		while (arg_node != NULL)
		{
			arg_node->data = strip_quotes(arg_node->data);
			envar_node = shell->env_list;
			while (envar_node->next != NULL)
			{
				if (ft_strcmp(envar_node->next->name, arg_node->data) == 0)
				{
					temp = envar_node->next->next;
					ft_env_lstdelone(&envar_node->next);
					envar_node->next = temp;
				}
				envar_node = envar_node->next;
			}
			arg_node = arg_node->left;
		}
	}
	return (SUCCESS);
}
