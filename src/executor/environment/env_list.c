#include "environment.h"
#include "../executor.h"

#include "libft.h"

#include <stdlib.h>

int	can_update_env_list(t_shell *shell, char *envar_name, char *string)
{
	char		*value_start;

	value_start = NULL;
	if (is_command(envar_name, string) == false)
	{
		value_start = string + ft_strlen(envar_name) + 1;
		if (update_env_list(shell, envar_name, value_start) == ERROR)
			return (ERROR);
	}
	return (SUCCESS);
}

/*
**  + 1 in envar_value is needed to skip the '=' sign
*/

int	create_env_list(t_shell *shell)
{
	extern char		**environ;
	char			*envar_name;
	char			*envar_value;
	int				i;

	envar_name = NULL;
	envar_value = NULL;
	i = 0;
	while (environ[i] != NULL)
	{
		envar_name = create_envar_name(environ[i]);
		envar_value = ft_strdup(environ[i] + ft_strlen(envar_name) + 1);
		if (!envar_name || !envar_value)
			return (ERROR);
		add_to_env_list(envar_name, envar_value, &shell->env_list);
		i++;
	}
	return (SUCCESS);
}

int	add_to_env_list(char *envar_name, char *envar_value, t_envlist	**env_list)
{
	t_envlist		*envar_node;

	envar_node = ft_env_lstnew(envar_name, envar_value);
	if (!envar_node)
		return (ERROR);
	ft_env_lstadd_back(env_list, envar_node);
	return (SUCCESS);
}

int	update_env_list(t_shell *shell, char *name, char *value_start)
{
	int			change_value_res;
	char		*envar_value;
	char		*envar_name;
	t_envlist	*envar_node;

	envar_value = NULL;
	envar_value = NULL;
	change_value_res = change_env_value(shell, name, value_start);
	if (change_value_res == ERROR)
		return (ERROR);
	else if (change_value_res == NOT_IN_ENVLIST)
	{
		envar_value = ft_strdup(value_start);
		envar_name = ft_strdup(name);
		if (envar_value == NULL)
			return (ERROR);
		envar_node = ft_env_lstnew(envar_name, envar_value);
		if (!envar_node)
			return (ERROR);
		ft_env_lstadd_before_last_node(&(shell->env_list), envar_node);
	}
	return (SUCCESS);
}
