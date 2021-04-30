/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcmp.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: osamara <osamara@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/28 16:06:06 by osamara       #+#    #+#                 */
/*   Updated: 2021/03/02 13:31:55 by osamara       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	index;

	if (n == 0)
		return (0);
	index = 0;
	while (index < n - 1
		&& ((unsigned char*)s1)[index] == ((unsigned char*)s2)[index])
	{
		index++;
	}
	return (((unsigned char*)s1)[index] - ((unsigned char*)s2)[index]);
}
