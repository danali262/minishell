/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstsize.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: osamara <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/06 09:49:12 by osamara       #+#    #+#                 */
/*   Updated: 2021/03/02 13:25:35 by osamara       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

int	ft_lstsize(t_list *lst)
{
	t_list	*element;
	int		size;

	if (lst == NULL)
	{
		return (0);
	}
	element = lst;
	size = 0;
	while (element != NULL)
	{
		size++;
		element = element->next;
	}
	return (size);
}
