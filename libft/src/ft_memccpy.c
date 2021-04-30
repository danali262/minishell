/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memccpy.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: osamara <osamara@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/28 12:43:42 by osamara       #+#    #+#                 */
/*   Updated: 2021/03/02 13:26:37 by osamara       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*dst_current;

	dst_current = dst;
	while (n > 0)
	{
		if (*((unsigned char *)src) == ((unsigned char)c))
		{
			*dst_current = *((unsigned char *)src);
			return (dst_current + 1);
		}
		else
		{
			*dst_current = *((unsigned char *)src);
			dst_current++;
			src++;
		}
		n--;
	}
	return (NULL);
}
