#include "executor.h"

#include "libft.h"

#include <stdlib.h>

char	*concat_path(char *left, char *right)
{
	char	*path;
	size_t	left_len;
	size_t	right_len;

	left_len = ft_strlen(left);
	right_len = ft_strlen(right);
	path = malloc(sizeof(char) * (left_len + right_len) + 2);
	if (!path)
	{
		printf("Error: unable to allocate memory for the path.\n");
		return (NULL);
	}
	ft_memmove(path, left, left_len);
	path[left_len] = '/';
	ft_memmove(path + left_len + 1, right, right_len);
	path[left_len + right_len + 1] = '\0';
	return (path);
}

#include <stdbool.h>

static char	*handle_data_with_quote(char *arg, char *temp, int *i, int *j)
{
    char    quote;
	char	*pairing_quote_pos;
	size_t	between_quotes_len;
	size_t	token_len;

    quote = arg[*i];
	token_len = ft_strlen(arg);
	between_quotes_len = 0;
	pairing_quote_pos = ft_strchr(arg + *i + 1, quote);
	if (pairing_quote_pos != NULL)
	{
		between_quotes_len = pairing_quote_pos - (arg + *i) - 1;
		ft_memcpy(temp + *j, arg + *i + 1, between_quotes_len);
		*i += between_quotes_len + 2;
		*j += between_quotes_len;
	}
	else
		ft_memcpy(temp + *j, arg + *i, token_len - *i);
	return (temp);
}

static char	*copy_value_iterate_index(char c, char *temp, int *i, int *j)
{
	temp[*j] = c;
	*i += 1;
	*j += 1;
	return (temp);
}

static char	*free_and_return(char *str_to_free, char *str_to_return)
{
	free(str_to_free);
	return (str_to_return);
}

char	*strip_quotes(char *arg)
{
	char	*temp;
	int		i;
	int		j;
	bool	is_quote_found;
	
	temp = ft_calloc(ft_strlen(arg) + 1, sizeof(char));
	if (!temp)
		return (NULL);
		i = 0;
	j = 0;
	is_quote_found = false;
	while (arg[i] != '\0')
	{
		if (arg[i] == '\'' || arg[i] == '"')
		{
			is_quote_found = true;
			temp = handle_data_with_quote(arg, temp, &i, &j);
		}
        else
			temp = copy_value_iterate_index(arg[i], temp,  &i, &j);
	}
	if (is_quote_found == false)
		return (free_and_return(temp, arg));
	return (free_and_return(arg, temp));
}

char *check_envars_and_quotes(t_treenode *arg_node, t_shell *shell)
{
	
	if (is_envar(arg_node))
	{
		arg_node->data = handle_argument_with_envvars(arg_node, shell);
		if (arg_node->data == NULL)
			return (NULL);
	}
	else
		arg_node->data = strip_quotes(arg_node->data);
	return (arg_node->data);
}