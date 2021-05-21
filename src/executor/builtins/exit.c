#include "builtins.h"

#include "libft.h"
#include <stdbool.h> 

int	count_arguments(t_treenode *simple_cmd_node)
{
	int			arg_num;
	t_treenode	*arg_node;

	arg_node = simple_cmd_node->left;
	arg_num = 0;
	while (arg_node != NULL)
	{
		arg_num++;
		arg_node = arg_node->left;
	}
	return (arg_num);
}

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
		printf("\nlogout\n-minishell: %s: too many arguments\n", simple_cmd_node->data);
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