#include "environment.h"

#include "libft.h"

#include <stdlib.h>

t_envlist	*ft_env_lstnew(char *name, char *value)
{
	t_envlist	*element;

	element = (t_envlist*)malloc(sizeof(t_envlist));
	if (element == NULL)
	{
		return (NULL);
	}
	element->name = name;
	element->value = value;
	element->next = NULL;
	return (element);
}

void	ft_env_lstadd_back(t_envlist **lst, t_envlist *new)
{
	t_envlist	*ptr;

	if (*lst == NULL)
		*lst = new;
	else
	{
		ptr = *lst;
		while (ptr->next != NULL)
		{
			ptr = ptr->next;
		}
		ptr->next = new;
	}
}

/*
** need to add the new environment variable to the last but one position
** as the last one in env is reserved for "_"
*/

void	ft_env_lstadd_before_last_node(t_envlist **lst, t_envlist *new)
{
	t_envlist	*ptr;

	if (*lst == NULL)
		*lst = new;
	else
	{
		ptr = *lst;
		while (ft_strncmp(ptr->next->name, "_", 2) != 0)
		{
			ptr = ptr->next;
		}
		new->next = ptr->next;
		ptr->next = new;
	}
}
