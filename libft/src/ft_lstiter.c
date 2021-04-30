/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstiter.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: osamara <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/06 14:43:02 by osamara       #+#    #+#                 */
/*   Updated: 2021/03/02 13:27:52 by osamara       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*current;

	if (lst == NULL)
	{
		return ;
	}
	current = lst;
	while (current != NULL)
	{
		f(current->content);
		current = current->next;
	}
}
