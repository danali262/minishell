#include "builtins.h"

#include "libft.h"

static int	is_n_option(t_treenode *arg_node)
{
	if (arg_node == NULL)
		return (0);
	if (ft_strncmp(arg_node->data, "-n", 3) == 0)
		return (1);
	return (0);
}

int	execute_echo(t_treenode *simple_cmd_node)
{
	t_treenode *arg_node;
	int			n_option;

	arg_node = simple_cmd_node->left;
	n_option = is_n_option(arg_node);
	if (n_option)
		arg_node = arg_node->left;
	while (arg_node != NULL)
	{
		// add the type check: whether it is the variable or the argument
		ft_putstr_fd(arg_node->data, STDOUT_FILENO);
		arg_node = arg_node->left;
		if (arg_node != NULL)
			ft_putstr_fd(" ", STDOUT_FILENO);
	}
	if (!n_option)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (1);
}
