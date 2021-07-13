#include "../executor.h"

#include "libft.h"

char	*create_envar_name(char *argument, bool *invalid_identifier_res)
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
	if (i == 0 || !has_alphanum_char(argument, i) || ft_isdigit(argument[0]))
	{
		printf("minishell: \'%s\': not a valid identifier\n\r", argument);
		*invalid_identifier_res = true;
	}
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
	while (envar_node != NULL)
	{
		if (is_command(envar_node->name, command))
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
		if (ft_strcmp(envar_node->value, new_value) != 0)
		{
			updated_value = ft_strtrim(new_value, "'\"");
			if (!updated_value)
				return (ERROR);
			if (ft_strcmp(var_name, "PWD") == 0)
				update_old_pwd(envar_node->value, shell);
			else
				free(envar_node->value);
			envar_node->value = updated_value;
		}
	}
	return (SUCCESS);
}

char	*replace_name_with_value(char *envvar_start, t_shell *shell,
			size_t *envvar_len)
{
	char	*value;
	char	*envvar_name;
	int		i;

	value = NULL;
	envvar_name = NULL;
	if (envvar_start[1] == '?')
	{
		value = replace_dollar_question(shell);
		*envvar_len = 2;
	}
	else
	{
		i = 1;
		while (is_allowed_in_envvar_name(envvar_start[i]))
			i++;
		*envvar_len = i;
		envvar_name = create_substring(envvar_start + 1, i - 1);
		value = get_envar_value(envvar_name, shell);
		free(envvar_name);
	}
	return (value);
}
