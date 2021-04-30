/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstmap.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: osamara <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/06 14:42:47 by osamara       #+#    #+#                 */
/*   Updated: 2021/03/02 13:25:58 by osamara       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*ptr;
	t_list	**nptr;

	if (lst == NULL || f == NULL)
		return (NULL);
	nptr = &new_lst;
	ptr = lst;
	while (ptr != NULL)
	{
		*nptr = (t_list*)malloc(sizeof(t_list));
		if (*nptr == NULL)
		{
			ft_lstclear(&new_lst, del);
			return (NULL);
		}
		(*nptr)->content = f(ptr->content);
		(*nptr)->next = NULL;
		ptr = ptr->next;
		nptr = &((*nptr)->next);
	}
	return (new_lst);
}
