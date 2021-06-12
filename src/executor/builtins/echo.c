#include "builtins.h"
#include "../executor.h"

#include "libft.h"

static int	is_n_option(t_treenode *arg_node)
{
	if (arg_node == NULL)
		return (0);
	if (ft_strncmp(arg_node->data, "-n", 3) == 0)
		return (1);
	return (0);
}

int	execute_echo(t_treenode *simple_cmd_node, t_shell *shell)
{
	t_treenode	*arg_node;
	int			n_option;
	char		*data_to_print;

	data_to_print = NULL;
	arg_node = simple_cmd_node->left;
	n_option = is_n_option(arg_node);
	if (n_option)
		arg_node = arg_node->left;
	while (arg_node != NULL)
	{
		if (ft_strchr(arg_node->data, '$') != NULL)
			data_to_print = handle_argument_with_envvars(arg_node, shell);
		else
			data_to_print = arg_node->data;
		ft_putstr_fd(data_to_print, STDOUT_FILENO);
		if (arg_node->left != NULL && arg_node->type != NODE_VAR)
			ft_putstr_fd(" ", STDOUT_FILENO);
		arg_node = arg_node->left;
	}
	if (!n_option)
		ft_putstr_fd("\n\r", STDOUT_FILENO);
	shell->exit_code = 0;
	return (SUCCESS);
}
