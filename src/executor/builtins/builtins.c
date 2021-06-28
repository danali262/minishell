#include "builtins_map.h"
#include "builtins.h"
#include "../executor.h"

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

int	execute_builtin(t_treenode *simple_cmd, t_builtins_map	*builtins_map,
		t_shell *shell)
{
	int	i;

	i = 0;
	while (builtins_map[i].cmd_name[0] != '\0')
	{
		if (is_command(builtins_map[i].cmd_name, simple_cmd->data))
		{
			shell->exit_code = builtins_map[i].cmd_executor(simple_cmd,
					shell);
			return (shell->exit_code);
		}
		i++;
	}
	return (NOT_BUILTIN);
}

int	can_execute_builtin(t_treenode *simple_cmd_node, t_shell *shell)
{
	static t_builtins_map	builtins_map[] =
	{
		{"echo", execute_echo},
		{"exit", execute_exit},
		{"cd", execute_cd},
		{"pwd", execute_pwd},
		{"export", execute_export},
		{"unset", execute_unset},
		{"env", execute_env},
		{"\0", NULL}
	};

	if (simple_cmd_node != NULL)
		return (execute_builtin(simple_cmd_node, builtins_map, shell));
	return (NOT_BUILTIN);
}
