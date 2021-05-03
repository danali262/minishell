/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnstr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: osamara <osamara@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/29 17:36:14 by osamara       #+#    #+#                 */
/*   Updated: 2021/03/02 13:30:04 by osamara       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	hstack_index;
	size_t	needle_location;
	size_t	i;

	if (*needle == '\0')
		return (((char*)haystack));
	hstack_index = 0;
	while (hstack_index < len && haystack[hstack_index] != '\0')
	{
		i = 0;
		needle_location = hstack_index;
		while (needle[i] != '\0' && needle_location < len
			&& (haystack[needle_location] == needle[i]))
		{
			i++;
			needle_location++;
		}
		if (needle[i] == '\0')
			return (((char*)&haystack[needle_location - i]));
		hstack_index++;
	}
	return (NULL);
}
