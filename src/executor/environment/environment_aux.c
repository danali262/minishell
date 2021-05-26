#include "environment.h"

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
