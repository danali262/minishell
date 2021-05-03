/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstnew.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: osamara <osamara@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/04 17:52:08 by osamara       #+#    #+#                 */
/*   Updated: 2021/03/02 13:30:42 by osamara       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstnew(void *content)
{
	t_list	*element;

	element = (t_list*)malloc(sizeof(t_list));
	if (element == NULL)
	{
		return (NULL);
	}
	element->content = content;
	element->next = NULL;
	return (element);
}
