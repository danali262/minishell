/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strncmp.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: osamara <osamara@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/29 20:09:09 by osamara       #+#    #+#                 */
/*   Updated: 2021/03/02 13:22:06 by osamara       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	index;
	unsigned char	*ptr1;
	unsigned char	*ptr2;

	ptr1 = (unsigned char *)s1;
	ptr2 = (unsigned char *)s2;
	index = 0;
	if (n == 0)
		return (0);
	while (index < n - 1 && *ptr1 == *ptr2)
	{
		if (*ptr1 == '\0' || *ptr2 == '\0')
		{
			break ;
		}
		index++;
		ptr1++;
		ptr2++;
	}
	return (*ptr1 - *ptr2);
}
