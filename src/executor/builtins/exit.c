#include "builtins.h"
#include "../executor.h"

#include "libft.h"
#include <stdbool.h> 

int	exit_with_code(t_treenode *arg_node, t_shell *shell)
{
	int		is_numeric_arg;

	is_numeric_arg = 0;
	arg_node->data = parse_argument_value(arg_node, shell);
	if (arg_node->data == NULL)
		return (ERROR);
	shell->exit_code = ft_minishell_atoi(arg_node->data,
			&is_numeric_arg);
	if (!is_numeric_arg)
	{
		printf("minishell: exit: %s: numeric argument required\n\r",
			arg_node->data);
		shell->exit_code = 255;
	}
	if (shell->redir->pipes_nbr == 0)
	{
		printf("exit\n\r");
		shell->minishell_exits = true;
	}
	return (shell->exit_code);
}

int	execute_exit(t_treenode *simple_cmd_node, t_shell *shell)
{
	int		arg_num;

	arg_num = count_arguments(simple_cmd_node);
	if (arg_num == 0)
	{
		printf("exit\n\r");
		shell->minishell_exits = true;
	}
	else if (arg_num > 1)
	{
		printf("exit\nminishell: %s: too many arguments\n",
			simple_cmd_node->data);
		return (ERROR);
	}
	else
		if (exit_with_code(simple_cmd_node->left, shell) == ERROR)
			return (ERROR);
	return (shell->exit_code);
}
