#include "builtins.h"

#include "libft.h"
#include <stdbool.h> 


int	execute_exit(t_treenode *simple_cmd_node, t_shell *shell)
{
	char	*exit_msg;
	int		arg_num;

	exit_msg = "exit";
	arg_num = count_arguments(simple_cmd_node);
	if (arg_num == 0)
	{
		printf("%s\n", exit_msg);
		shell->exit_code = 0;
		shell->minishell_exits = true;
	}
	else if (arg_num > 1)
	{
		printf("\nlogout\n-minishell: %s: too many arguments\n",
				simple_cmd_node->data);
		return (0);
	}
	else
	{
		shell->exit_code = ft_atoi(simple_cmd_node->left->data);
		shell->minishell_exits = true;
		return (0);
	}
	return (1);
}
