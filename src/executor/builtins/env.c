#include "builtins.h"
#include "../executor.h"

int	execute_env(t_treenode *simple_cmd_node, t_shell *shell)
{
	t_envlist	*node;

	node = shell->env_list;
	while (node != NULL)
	{
		if (is_command(simple_cmd_node->data, "export"))
			printf("declare -x %s\"=%s\"\n", node->name, node->value);
		else
			printf("%s=%s\n", node->name, node->value);
		node = node->next;
	}
	return (SUCCESS);
}
