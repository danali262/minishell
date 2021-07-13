#include "executor.h"

static char	*append_tilde_value(char *path)
{
	char	*tilde_value;
	char	*temp;

	tilde_value = ft_strdup(getenv("HOME"));
	if (path[1] == '\0')
	{
		free(path);
		return (tilde_value);
	}
	temp = ft_strdup(path + 2);
	free(path);
	path = concat_path(tilde_value, temp);
	free(tilde_value);
	free(temp);
	return (path);
}

char	*parse_argument_value(t_treenode *simple_cmd_node, t_shell *shell)
{
	char	*command;

	if (simple_cmd_node->data[0] == '~'
		&& (simple_cmd_node->data[1] == '\0' || simple_cmd_node->data[1] == '/'))
		simple_cmd_node->data = append_tilde_value(simple_cmd_node->data);
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
	new_arg_value = create_new_argument_string(arg_node->data, shell);
	if (new_arg_value != NULL)
		string_without_quotes = strip_quotes(new_arg_value);
	return (string_without_quotes);
}
