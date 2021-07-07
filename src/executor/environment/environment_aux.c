#include "environment.h"
#include "../executor.h"

#include "libft.h"

#include <stdlib.h>
#include <stdbool.h>

int	has_alpha_char(char *name, int length)
{
	int	i;

	i = 0;
	while (i < length)
	{
		if (is_allowed_in_envvar_name(name[i]))
			return (true);
		i++;
	}
	return (false);
}

bool	is_allowed_in_envvar_name(char c)
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')
		|| (c >= '0' && c <= '9') || (c == '_'));
}

void	update_old_pwd(char	*current_pwd_value, t_shell *shell)
{
	t_envlist	*envar_node;
	bool		is_oldpwd_set;

	envar_node = shell->env_list;
	is_oldpwd_set = false;
	while (envar_node != NULL)
	{
		if (ft_strcmp(envar_node->name, "OLDPWD") == 0)
		{
			is_oldpwd_set = true;
			free(envar_node->value);
			envar_node->value = current_pwd_value;
			break ;
		}
		envar_node = envar_node->next;
	}
	if (!is_oldpwd_set)
	{
		update_env_list(shell, "OLDPWD", current_pwd_value);
		free(current_pwd_value);
	}
}

t_envlist	*get_node_to_change(t_shell *shell, char *var_name)
{
	t_envlist	*envar_node;

	envar_node = shell->env_list;
	while (envar_node != NULL)
	{
		if (ft_strcmp(envar_node->name, var_name) == 0)
			return (envar_node);
		envar_node = envar_node->next;
	}
	return (NULL);
}

bool	contains_char(char *argument_string, char character)
{
	if (ft_strchr(argument_string, character) == NULL)
		return (false);
	return (true);
}
