/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcpy.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: osamara <osamara@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/27 15:21:10 by osamara       #+#    #+#                 */
/*   Updated: 2021/03/02 13:26:58 by osamara       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*dst_current;

	if (!src && !dst)
		return (0);
	dst_current = dst;
	while (n > 0)
	{
		*dst_current = *((unsigned char *)src);
		dst_current++;
		src++;
		n--;
	}
	return (dst);
}
