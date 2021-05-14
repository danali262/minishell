#include "builtins_map.h"
#include "builtins.h"

#include "libft.h"

int	execute_echo(t_lexer *lexerbuf)
{
	if (ft_strncmp(lexerbuf->tokens_list->next->data, "-n", 3) == 0)
		ft_putstr_fd(lexerbuf->tokens_list->next->next->data, STDOUT_FILENO);
	else
	{
		ft_putstr_fd(lexerbuf->tokens_list->next->data, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
	}
	return (1);
}

int	can_execute_builtin(t_lexer *lexerbuf)
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
		// {"exit", execute_exit},
		{"\0", NULL}
	};

	i = 0;
	while (builtins_map[i].cmd_name[0] != '\0')
	{
		if (ft_strncmp(builtins_map[i].cmd_name, lexerbuf->tokens_list->data,
			ft_strlen(builtins_map[i].cmd_name)) == 0)
		{
			if (!builtins_map[i].cmd_executor(lexerbuf))
				return (-1); // if error in execution function
			else
				return (1);
		}
		i++;
	}
		return (0); // if no command found
}