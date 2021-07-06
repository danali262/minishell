#include "libft.h"

bool	ft_isnumber(char *string)
{
	if (string == NULL)
		return (false);
	while (*string != '\0')
	{
		if (!ft_isdigit(*string))
			return (false);
		string++;
	}
	return (true);
}