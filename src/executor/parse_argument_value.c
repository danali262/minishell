#include "executor.h"

char	*parse_argument_value(t_treenode *simple_cmd_node, t_shell *shell)
{
	char	*command;

	if (contains_char(simple_cmd_node->data, '$'))
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
	if (!is_wrapped_in_single_quotes(arg_node->data))
	{
		new_arg_value = create_new_argument_string(arg_node->data, shell);
		if (new_arg_value != NULL)
			string_without_quotes = strip_quotes(new_arg_value);
	}
	else
		string_without_quotes = strip_quotes(arg_node->data);
	return (string_without_quotes);
}
