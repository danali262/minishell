#include "builtins_map.h"
#include "builtins.h"

#include "libft.h"


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

int	can_execute_builtin(t_treenode *simple_cmd_node, t_shell *shell)
{
	int		i;
	static t_builtins_map	builtins_map[] =
	{
		{"echo", execute_echo},
		{"exit", execute_exit},
		{"cd", execute_cd},
		{"pwd", execute_pwd},
		// {"export", execute_export},
		// {"unset", execute_unset},
		// {"env", execute_env},
		{"\0", NULL}
	};
	if (simple_cmd_node != NULL)
	{
		i = 0;
		while (builtins_map[i].cmd_name[0] != '\0')
		{
			if (ft_strncmp(builtins_map[i].cmd_name, simple_cmd_node->data,
					ft_strlen(builtins_map[i].cmd_name)) == 0)
			{
				shell->exit_code = builtins_map[i].cmd_executor(simple_cmd_node, shell);
				return (shell->exit_code); // if error in execution function, if no malloc, don't have to exit minishell
			}
			i++;
		}
	}
	return (NOT_BUILTIN); // if no command found
}
