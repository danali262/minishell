/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strdup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: osamara <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/24 13:39:47 by osamara       #+#    #+#                 */
/*   Updated: 2021/03/02 13:18:48 by osamara       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strdup(const char *s1)
{
	const char	*dest;
	const char	*dest1;

	dest = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (dest == NULL)
		return (NULL);
	dest1 = dest;
	while (*s1)
	{
		*((char *)dest) = *((char *)s1);
		dest++;
		s1++;
	}
	*((char *)dest) = '\0';
	return (((char *)dest1));
}
