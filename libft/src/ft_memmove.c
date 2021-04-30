/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memmove.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: osamara <osamara@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/27 15:20:51 by osamara       #+#    #+#                 */
/*   Updated: 2021/03/02 13:19:40 by osamara       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*move_forward(void *dst, const void *src, size_t len)
{
	unsigned char		*dst_current;
	const unsigned char	*src_current;

	src_current = src;
	dst_current = dst;
	while (len > 0)
	{
		*dst_current = *src_current;
		dst_current++;
		src_current++;
		len--;
	}
	return (dst);
}

static void	*move_backwards(void *dst, const void *src, size_t len)
{
	unsigned char		*dst_current;
	const unsigned char	*src_current;

	dst_current = dst + (len - 1);
	src_current = src + (len - 1);
	while (len > 0)
	{
		*dst_current = *src_current;
		dst_current--;
		src_current--;
		len--;
	}
	return (dst);
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	if (!src && !dst)
		return (0);
	if (len == 0)
		return (dst);
	if (src < dst)
	{
		return (move_backwards(dst, src, len));
	}
	else
	{
		return (move_forward(dst, src, len));
	}
}
