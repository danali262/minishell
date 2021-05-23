#include "lexer.h"

void	lexer_error(t_token *tokens_list)
{
	t_token	*head;

	ft_putstr_fd("Malloc error.\n", STDOUT_FILENO);
	head = tokens_list;
	while (head != NULL)
	{
		free_token(head);
		head = head->next;
	}
	exit(0);
}
