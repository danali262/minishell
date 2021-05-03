/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcpy.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: osamara <osamara@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/28 17:40:39 by osamara       #+#    #+#                 */
/*   Updated: 2021/03/02 13:32:24 by osamara       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	index;

	if (!dst || !src)
		return (0);
	index = 0;
	if (dstsize != 0)
	{
		while (index < dstsize - 1)
		{
			if (src[index] == '\0')
			{
				break ;
			}
			dst[index] = src[index];
			index++;
		}
		dst[index] = '\0';
	}
	return (ft_strlen(src));
}
