#include "builtins.h"
#include "../executor.h"

#include "libft.h"

static int	export_envar(t_treenode *arg_node, t_shell *shell)
{
	char	*envar_name;

	envar_name = NULL;
	while (arg_node != NULL)
	{
		arg_node->data = parse_argument_value(arg_node, shell);
		if (arg_node->data == NULL)
			return (ERROR);
		envar_name = create_envar_name(arg_node->data);
		if (envar_name == NULL)
			return (ERROR);
		if (can_update_env_list(shell, envar_name, arg_node->data) == ERROR)
		{
			free(envar_name);
			return (ERROR);
		}
		arg_node = arg_node->left;
		free(envar_name);
	}
	return (SUCCESS);
}

int	execute_export(t_treenode *simple_cmd_node, t_shell *shell)
{
	if (simple_cmd_node->left == NULL)
		execute_env(simple_cmd_node, shell);
	else
	{
		if (export_envar(simple_cmd_node->left, shell) == ERROR)
			return (ERROR);
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
				if (is_command(envar_node->next->name, arg_node->data))
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
