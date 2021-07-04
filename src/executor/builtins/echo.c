#include "builtins.h"
#include "../executor.h"

#include "libft.h"

static int	is_n_option(t_treenode *arg_node)
{
	if (arg_node == NULL)
		return (0);
	arg_node->data = strip_quotes(arg_node->data);
	if (ft_strncmp(arg_node->data, "-n", 3) == 0)
		return (1);
	return (0);
}

int	execute_echo(t_treenode *simple_cmd_node, t_shell *shell)
{
	t_treenode	*arg_node;
	int			n_option;

	arg_node = simple_cmd_node->left;
	n_option = is_n_option(arg_node);
	if (n_option)
	{
		shell->is_newline = false;
		arg_node = arg_node->left;
	}
	while (arg_node != NULL)
	{
		arg_node->data = parse_argument_value(arg_node, shell);
		if (arg_node->data == NULL)
			return (ERROR);
		ft_putstr_fd(arg_node->data, STDOUT_FILENO);
		if (arg_node->left != NULL && arg_node->type != NODE_VAR)
			ft_putstr_fd(" ", STDOUT_FILENO);
		arg_node = arg_node->left;
	}
	if (!n_option)
		ft_putstr_fd("\n\r", STDOUT_FILENO);
	shell->exit_code = 0;
	return (SUCCESS);
}
