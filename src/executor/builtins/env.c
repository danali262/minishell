#include "builtins.h"
#include "../executor.h"

#include "libft.h"

int execute_env(t_treenode *simple_cmd_node, t_shell *shell)
{
	t_envlist *node;

	if (simple_cmd_node)
	{

		node = shell->env_list; 
		while (node->next != NULL)
		{
			printf("%s=%s\n", node->name, node->value);
			node = node->next;
		}
	}
	return (SUCCESS);
}