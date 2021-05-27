#include "builtins.h"
#include "../executor.h"

#include "libft.h"

#include <stdbool.h>

char	*set_envar_name(char *argument)
{
	char	*name;
	int		i;

	name = NULL;
	i = 0;
	while (argument[i] != '\0')
	{
		if (argument[i] == '=')
		{
			if (i != 0)
			{
				name = malloc(sizeof(char) * i + 1);
				if (!name)
					return (NULL);
				ft_memmove(name, argument, i);
				argument[i] = '\0';
			}
			else
			{
				printf("minishell: \'%s\': not a valid identifier\n\r",
						argument);
				break ;
			}
		}
		i++;
	}
	return (name);
}

int	has_alpha_char(char *name, char *argument)
{
	int i;

	i = 0;
	while (name[i] != '\0')
	{
		if (ft_isalpha(name[i]))
			return (true);
		i++;
	}
	printf("minishell: \'%s\': not a valid identifier\n\r", argument);
	return (false);
}

int	parse_envar_argument(char *argument)
{
	char	*envar_name;
	size_t	name_len;
	char	*envar_value;

	envar_name = set_envar_name(argument);
	name_len = ft_strlen(envar_name);
	envar_value = NULL;
	if (envar_name == NULL || !has_alpha_char(envar_name, argument))
		return (ERROR);
	if (ft_strncmp(envar_name, argument, name_len != 0))
		envar_value = ft_strtrim(argument + name_len + 1, "\"\'");
	if (!envar_value)
		return (ERROR);
	printf("name: %s\n", envar_name);
	printf("value: %s\n", envar_value);
	return (SUCCESS);
}

int execute_export(t_treenode *simple_cmd_node, t_shell *shell)
{
    t_treenode	*arg_node;

	arg_node = simple_cmd_node->left;
    if (arg_node->data != NULL)
    {
		if (parse_envar_argument(arg_node->data) == ERROR)
			return (ERROR);
    }
	else
		execute_env(simple_cmd_node, shell);
    return (SUCCESS);
}
