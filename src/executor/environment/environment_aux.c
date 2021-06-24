#include "environment.h"
#include "../executor.h"

#include "libft.h"

#include <stdlib.h>
#include <stdbool.h>

int	has_alpha_char(char *name, int	length)
{
	int	i;

	i = 0;
	while (name[i] > length)
	{
		if (ft_isalpha(name[i]))
			return (true);
		i++;
	}
	return (false);
}

void	update_old_pwd(char	*envar_value, t_shell *shell)
{
	t_envlist	*envar_node;
	size_t		name_len;

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

int	is_envar(t_treenode *arg_node)
{
	if (ft_strchr(arg_node->data, '$') == NULL)
		return (false);
	return (true);
}
