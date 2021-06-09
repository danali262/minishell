#include "../executor.h"

#include "libft.h"

char	*get_envar_name(char *argument)
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

char	*get_envar_value(char *command, t_shell *shell)
{
	t_envlist	*envar_node;
	char		*value;

	envar_node = shell->env_list;
	value = NULL;
	while (envar_node->next != NULL)
	{
		if (ft_strncmp(envar_node->name, command, ft_strlen(command) + 1) == 0)
		{
			value = ft_strdup(envar_node->value);
			break ;
		}
		envar_node = envar_node->next;
	}
	return (value);
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

int	is_envar(t_treenode *arg_node)
{
	if (arg_node->data[0] == '$' && arg_node->left == NULL)
		return (1);
	return (0);
}

char	*replace_name_with_value(t_treenode *arg_node, t_shell *shell)
{
	char	*value;

	value = NULL;
	if (arg_node->data[1] == '?')
		value = replace_dollar_question(arg_node, shell);
	else
		value = get_envar_value(arg_node->data + 1, shell);
	return (value);
}
