/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcat.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: osamara <osamara@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/28 18:02:59 by osamara       #+#    #+#                 */
/*   Updated: 2021/03/02 13:19:20 by osamara       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	src_index;
	size_t	dst_len;
	size_t	src_len;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	src_index = 0;
	if (dst_len >= dstsize)
		return (dstsize + src_len);
	while ((dst_len + src_index) < (dstsize - 1) && src[src_index] != '\0')
	{
		dst[dst_len + src_index] = src[src_index];
		src_index++;
	}
	if (dstsize != 0)
	{
		dst[dst_len + src_index] = '\0';
	}
	return (dst_len + src_len);
}
