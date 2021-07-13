#include "executor.h"

char	*parse_argument_value(t_treenode *simple_cmd_node, t_shell *shell)
{
	char	*command;

		if (is_command("~", simple_cmd_node->data))
		{
			free(simple_cmd_node->data);
			simple_cmd_node->data = ft_strdup(getenv("HOME"));
		}
	
else	if (contains_char(simple_cmd_node->data, '$'))
	{
		command = handle_argument_with_envvars(simple_cmd_node, shell);
		if (command == NULL)
			return (NULL);
		simple_cmd_node->data = command;
	}
	else
		simple_cmd_node->data = strip_quotes(simple_cmd_node->data);
	return (simple_cmd_node->data);
}

char	*handle_argument_with_envvars(t_treenode *arg_node, t_shell *shell)
{
	char	*new_arg_value;
	char	*string_without_quotes;

	string_without_quotes = NULL;
	new_arg_value = create_new_argument_string(arg_node->data, shell);
	if (new_arg_value != NULL)
		string_without_quotes = strip_quotes(new_arg_value);
	return (string_without_quotes);
}
