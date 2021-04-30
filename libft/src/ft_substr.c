/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_substr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: osamara <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/30 14:21:11 by osamara       #+#    #+#                 */
/*   Updated: 2021/03/02 13:22:22 by osamara       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*substring;
	unsigned int	index;

	if (!s)
		return (NULL);
	substring = (char *)malloc(sizeof(char) * (len + 1));
	if (substring == NULL)
		return (NULL);
	index = 0;
	while (*s != '\0' && index < len && start < ft_strlen(s))
	{
		substring[index] = ((char *)s)[index + start];
		index++;
	}
	substring[index] = '\0';
	return (substring);
}
