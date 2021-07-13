#include "executor.h"

#include "libft.h"

#include <stdbool.h>

static char	*handle_data_with_quote(char *arg, char *temp, int *i, int *j)
{
	char	quote;
	char	*pairing_quote_pos;
	size_t	between_quotes_len;
	size_t	token_len;

	quote = arg[*i];
	token_len = ft_strlen(arg);
	between_quotes_len = 0;
	pairing_quote_pos = ft_strchr(arg + *i + 1, quote);
	if (pairing_quote_pos == NULL)
		between_quotes_len = (arg + token_len) - (arg + *i) - 1;
	else
		between_quotes_len = pairing_quote_pos - (arg + *i) - 1;
	ft_memcpy(temp + *j, arg + *i + 1, between_quotes_len);
	*i += between_quotes_len + 1;
	if (pairing_quote_pos)
		i++;
	*j += between_quotes_len;
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
			temp = copy_value_iterate_index(arg[i], temp, &i, &j);
	}
	if (is_quote_found == false)
		return (free_and_return(temp, arg));
	return (free_and_return(arg, temp));
}
