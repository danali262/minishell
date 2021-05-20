#include "builtins_map.h"
#include "builtins.h"

#include "libft.h"


int	is_n_option(t_treenode *arg_node)
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
		ft_putstr_fd(arg_node->data, STDOUT_FILENO);
		ft_putstr_fd(" ", STDOUT_FILENO);
		arg_node = arg_node->left;
	}
	ft_putstr_fd("\b", STDOUT_FILENO);
	if (!n_option)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (1);
}

int	can_execute_builtin(t_treenode *simple_cmd_node, t_shell *shell)
{
	int		i;
	static t_builtins_map	builtins_map[] =
	{
		{"echo", execute_echo},
		// {"cd", execute_cd},
		// {"pwd", execute_pwd},
		// {"export", execute_export},
		// {"unset", execute_unset},
		// {"env", execute_env},
		{"\0", NULL}
	};

	if (simple_cmd_node != NULL)
	{
		if (ft_strncmp("exit", simple_cmd_node->data, 5) == 0)
        {
            execute_exit(simple_cmd_node, shell);
            return (1);
        }
		i = 0;
		while (builtins_map[i].cmd_name[0] != '\0')
		{
			if (ft_strncmp(builtins_map[i].cmd_name, simple_cmd_node->data,
					ft_strlen(builtins_map[i].cmd_name)) == 0)
			{
				if (!builtins_map[i].cmd_executor(simple_cmd_node))
					return (-1); // if error in execution function
				else
					return (1);
			}
			i++;
		}
	}
	return (0); // if no command found
}
