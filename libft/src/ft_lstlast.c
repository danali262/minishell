/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstlast.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: osamara <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/06 10:27:31 by osamara       #+#    #+#                 */
/*   Updated: 2021/03/02 13:31:26 by osamara       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*current;

	if (lst == NULL)
	{
		return (lst);
	}
	else
	{
		current = lst;
		while (current->next != NULL)
		{
			current = current->next;
		}
	}
	return (current);
}
