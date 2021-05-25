#include "environment.h"
#include "../executor.h"

#include "libft.h"

#include <stdlib.h>

char	*get_envar_name(char *env_string)
{
	int		i;
	char	*envar_name;

	i = 0;
	envar_name = NULL;
	while (env_string[i] != '\0')
	{
		if (env_string[i] == '=')
			break ;
		i++;
	}
	envar_name = malloc(sizeof(char) * i);
	if (!envar_name)
		return (NULL);
	ft_memmove(envar_name, env_string, i);
	envar_name[i] = '\0';
	return (envar_name);
}

int	copy_environ(t_envlist	**env_list)
{
	extern char		**environ;
	t_envlist		*envar_node;
	char			*envar_name;
	char			*envar_value;
	int				i;

	envar_node = NULL;
	envar_name = NULL;
	envar_value = NULL;
	i = 0;
	while (environ[i] != NULL)
	{
		envar_name = get_envar_name(environ[i]);
		envar_value = ft_strdup(environ[i] + ft_strlen(envar_name) + 1); // + 1 is needed to skip the = sign
		if (!envar_name || !envar_value)
			return (ERROR);
		envar_node = ft_env_lstnew(envar_name, envar_value);
		if (!envar_node)
			return (ERROR);
		ft_env_lstadd_back(env_list, envar_node);
		i++;
	}
	envar_name = get_envar_name("_");
	envar_value = ft_strdup("/usr/bin/env");
	envar_node = ft_env_lstnew(envar_name, envar_value);
	ft_env_lstadd_back(env_list, envar_node);
	return (SUCCESS);
}

int	create_env_list(t_shell *shell)
{
    t_envlist	*env_list;
	
	env_list = NULL;
	if (copy_environ(&env_list) == ERROR)
	 return (ERROR);
	shell->env_list = env_list;
// env_list printing function:

	// t_envlist *node = shell->env_list; 
	// while (node->next != NULL)
	// {
	// 	printf("%s=%s\n", node->name, node->value);
	// 	node = node->next;
	// }
	return (SUCCESS);
}

int	create_export_list(t_shell *shell)
{
    t_envlist	*export_list;
	
	export_list = NULL;
	if (copy_environ(&export_list) == ERROR)
	 return (ERROR);
	shell->export_list = export_list;
// export_list printing function:

	// t_envlist *node = shell->export_list; 
	// while (node->next != NULL)
	// {
	// 	printf("declare -x %s=\"%s\"\n", node->name, node->value);
	// 	node = node->next;
	// }
	return (SUCCESS);
}

void	update_old_pwd(char	*envar_value, t_shell *shell)
{
	t_envlist	*envar_node;
	size_t	name_len;

	name_len = ft_strlen("OLD_PWD");
	envar_node = shell->env_list;
	while (envar_node->next != NULL)
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

int	change_env_value(t_shell *shell, char *var_name, char *new_value)
{
	size_t		name_len;
	size_t		new_value_len;
	char		*updated_value;
	t_envlist	*envar_node;

	updated_value = NULL;
	name_len = ft_strlen(var_name);
	new_value_len = ft_strlen(new_value);
	updated_value = ft_strdup(new_value);
	if (!updated_value)
		return (ERROR);
	
	envar_node = shell->env_list;
	while (envar_node->next != NULL)
	{
		if (ft_strncmp(envar_node->name, var_name, name_len + 1) == 0)
			break ;
		envar_node = envar_node->next;
	}
	if (ft_strncmp(var_name, "PWD", 4) == 0)
		update_old_pwd(envar_node->value, shell);
	else
		free(envar_node->value);
	envar_node->value = updated_value;
	return (SUCCESS);
}

int	create_environment(t_shell *shell)
{
	if (create_env_list(shell) == ERROR || create_export_list(shell) == ERROR)
		return (ERROR);
		shell->local_var_list = NULL;
	return (SUCCESS);
}