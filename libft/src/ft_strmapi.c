/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strmapi.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: osamara <osamara@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/02 20:10:54 by osamara       #+#    #+#                 */
/*   Updated: 2021/03/02 13:21:46 by osamara       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*new_str;
	size_t			length;
	unsigned int	index;

	if (!s || !f)
		return (NULL);
	length = ft_strlen(s);
	new_str = (char *)malloc(sizeof(char) * (length + 1));
	if (new_str == NULL)
		return (NULL);
	index = 0;
	while (index < length)
	{
		*new_str = f(index, *((char *)s));
		index++;
		new_str++;
		s++;
	}
	*new_str = '\0';
	return (new_str - length);
}
