#include "builtins.h"
#include "../executor.h"

#include "libft.h"

int	update_env_list(t_shell *shell, char *envar_name, char *value_start)
{
	int			change_value_res;
	char		*envar_value;
	t_envlist	*envar_node;

	change_value_res = change_env_value(shell, envar_name, value_start);
	if (change_value_res == ERROR)
			return (ERROR);
	else if (change_value_res == NOT_IN_ENVLIST)
	{
		envar_value = ft_strtrim(value_start, "'\"");
		if (envar_value == NULL)
			return (ERROR);
		envar_node = ft_env_lstnew(envar_name, envar_value);
		if (!envar_node)
			return (ERROR);
		ft_env_lstadd_before_last_node(&(shell->env_list), envar_node);
	}
	
	// 		t_envlist *node = shell->env_list; 
// 		while (node != NULL)
// 		{
// 			printf("%s=%s\n", node->name, node->value);
// 			node = node->next;
// 		}
	return (SUCCESS);
}

int execute_export(t_treenode *simple_cmd_node, t_shell *shell)
{
    t_treenode	*arg_node;
	char		*envar_name;
	char		*value_start;
	size_t		name_len;

	value_start = NULL;
	if (simple_cmd_node->left == NULL)
		execute_env(simple_cmd_node, shell);
	else
	{
		arg_node = simple_cmd_node->left;
		while (arg_node != NULL)
		{
			envar_name = get_envar_name(arg_node->data);
			if (envar_name == NULL)
				return (ERROR);
			name_len = ft_strlen(envar_name);
			if (ft_strncmp(envar_name, arg_node->data, name_len + 1) != 0)
			{
				value_start = arg_node->data + name_len + 1;
				if (update_env_list(shell, envar_name, value_start) == ERROR)
					return (ERROR);
			}
			arg_node = arg_node->left;
		}
	}
    return (SUCCESS);
}
