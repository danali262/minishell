#include "executor.h"

#include "libft.h"

#include <stdbool.h>

static char	*get_cur_quote_pos(char	*quote_position, char *string)
{
	if (quote_position == NULL)
		quote_position = string;
	else
		quote_position = NULL;
	return (quote_position);
}

bool	is_wrapped_in_single_quotes(char *string, char *dollar_sign_position)
{
	char	*single_quote_position;
	char	*double_quote_position;

	single_quote_position = NULL;
	double_quote_position = NULL;
	while (string < dollar_sign_position)
	{
		if (*string == '\'')
			single_quote_position = get_cur_quote_pos(single_quote_position,
					string);
		else if (*string == '"')
			double_quote_position = get_cur_quote_pos(double_quote_position,
					string);
		string++;
	}
	if (single_quote_position != NULL)
	{
		if (double_quote_position == NULL)
			return (true);
		else
			if (double_quote_position > single_quote_position)
				return (true);
	}
	return (false);
}
