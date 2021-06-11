#include "builtins.h"

#include "libft.h"
#include <stdbool.h> 

void	exit_with_code(t_treenode *simple_cmd_node, t_shell *shell)
{
	int		is_numeric_arg;

	is_numeric_arg = 0;
	shell->exit_code = ft_printf_atoi(simple_cmd_node->left->data,
			&is_numeric_arg);
	if (!is_numeric_arg)
	{
		printf("exit\n\r");
		printf("minishell: exit: %s: numeric argument required\n\r",
			simple_cmd_node->left->data);
		shell->exit_code = 255;
	}
	shell->minishell_exits = true;
}

int	execute_exit(t_treenode *simple_cmd_node, t_shell *shell)
{
	int		arg_num;

	arg_num = count_arguments(simple_cmd_node);
	if (arg_num == 0)
	{
		printf("exit\n\r");
		shell->exit_code = 0;
		shell->minishell_exits = true;
	}
	else if (arg_num > 1)
	{
		printf("exit\nminishell: %s: too many arguments\n",
			simple_cmd_node->data);
		return (ERROR);
	}
	else
		exit_with_code(simple_cmd_node, shell);
	return (SUCCESS);
}
