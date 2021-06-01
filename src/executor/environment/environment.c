#include "environment.h"
#include "../executor.h"

#include "libft.h"

#include <stdlib.h>
#include <stdbool.h>

int	has_alpha_char(char *name, int	length)
{
	int i;

	i = 0;
	while (name[i] > length)
	{
		if (ft_isalpha(name[i]))
			return (true);
		i++;
	}
	return (false);
}

char	*set_envar_name(char *argument)
{
	char	*name;
	int		i;

	name = NULL;
	i = 0;
	while (argument[i] != '\0')
	{
		if (argument[i] == '=')
			break ;
		i++;
	}
	if (i == 0 || !has_alpha_char(argument, i))
		printf("minishell: \'%s\': not a valid identifier\n\r", argument);
	else
	{
		name = malloc(sizeof(char) * i + 1);
		if (!name)
			return (NULL);
		ft_memmove(name, argument, i);
		name[i] = '\0';
	}
	return (name);
}


int add_to_env_list(char *envar_name, char *envar_value, t_envlist	**env_list)
{
	t_envlist		*envar_node;
	
	envar_node = ft_env_lstnew(envar_name, envar_value);
	if (!envar_node)
		return (ERROR);
	ft_env_lstadd_back(env_list, envar_node);
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
		envar_name = set_envar_name(environ[i]);
		if (ft_strncmp(envar_name, "_", 2) == 0)
			envar_value = ft_strdup("");
		else
			envar_value = ft_strdup(environ[i] + ft_strlen(envar_name) + 1);
		if (!envar_name || !envar_value)
			return (ERROR);
		add_to_env_list(envar_name, envar_value, &shell->env_list);
		i++;
	}
	return (SUCCESS);
}

void	update_old_pwd(char	*envar_value, t_shell *shell)
{
	t_envlist	*envar_node;
	size_t	name_len;

	name_len = ft_strlen("OLD_PWD");
	envar_node = shell->env_list;
	while (envar_node != NULL)
	{
		if (ft_strncmp(envar_node->name, "OLD_PWD", name_len + 1) == 0)
		{
			free(envar_node->value);
			envar_node->value = envar_value;
			break ;
		}
		envar_node = envar_node->next;
	}
}

t_envlist	*get_node_to_change(t_shell *shell, char *var_name)
{
	size_t		name_len;
	t_envlist	*envar_node;

	name_len = ft_strlen(var_name);
	envar_node = shell->env_list;
	while (envar_node != NULL)
	{
		if (ft_strncmp(envar_node->name, var_name, name_len + 1) == 0)
			return (envar_node);
		envar_node = envar_node->next;
	}
	return (NULL);
}

int	change_env_value(t_shell *shell, char *var_name, char *new_value)
{
	char		*updated_value;
	t_envlist	*envar_node;

	updated_value = NULL;
	envar_node = get_node_to_change(shell, var_name);
	if (envar_node == NULL)
		return (NOT_IN_ENVLIST);
	else
	{
		if (ft_strncmp(envar_node->value, new_value,
				ft_strlen(envar_node->value)) != 0)
		{
			updated_value = ft_strtrim(new_value, "'\"");
			if (!updated_value)
				return (ERROR);
			if (ft_strncmp(var_name, "PWD", 4) == 0)
				update_old_pwd(envar_node->value, shell);
			else
				free(envar_node->value);
			envar_node->value = updated_value;	
		}
	}
	return (SUCCESS);
}
