#include "builtins.h"
#include "../executor.h"

#include "libft.h"
#include <stdbool.h> 

void	exit_with_code(t_treenode *arg_node, t_shell *shell)
{
	int		is_numeric_arg;
	char 	*argument;

	is_numeric_arg = 0;
	argument = NULL;
	if (is_envar(arg_node))
	{
		arg_node->data = handle_argument_with_envvars(arg_node, shell);
		if (argument != NULL)
			arg_node->data = argument;
	}
	else
		arg_node->data = strip_quotes(arg_node->data);
	shell->exit_code = ft_minishell_atoi(arg_node->data,
			&is_numeric_arg);
	printf("exit\n\r");
	if (!is_numeric_arg)
	{
		printf("minishell: exit: %s: numeric argument required\n\r",
			arg_node->data);
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
		exit_with_code(simple_cmd_node->left, shell);
	return (SUCCESS);
}
