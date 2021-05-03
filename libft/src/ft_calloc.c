/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_calloc.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: osamara <osamara@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/30 06:34:10 by osamara       #+#    #+#                 */
/*   Updated: 2020/11/10 17:59:30 by osamara       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	space_n;

	space_n = count * size;
	ptr = malloc(space_n);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, space_n);
	return (ptr);
}
