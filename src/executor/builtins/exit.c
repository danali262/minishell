#include "builtins.h"

#include "libft.h"
#include <stdbool.h> 


int	execute_exit(t_treenode *simple_cmd_node, t_shell *shell)
{
	char	*exit_msg;
	int		arg_num;
	int		is_numeric_arg;

	exit_msg = "exit";
	arg_num = count_arguments(simple_cmd_node);
	is_numeric_arg = 0;
	if (arg_num == 0)
	{
		printf("%s\n\r", exit_msg);
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
		shell->exit_code = ft_printf_atoi(simple_cmd_node->left->data,
			&is_numeric_arg);
		if (!is_numeric_arg)		
		{
			printf("%s\n\r", exit_msg);
			printf("minishell: exit: %s: numeric argument required\n\r", simple_cmd_node->left->data);
			shell->exit_code = 255;
		}
		shell->minishell_exits = true;
		return (1);
	}
	return (1);
}
