#include "builtins_map.h"
#include "builtins.h"

#include "libft.h"


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
