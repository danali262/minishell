#include "minishell.h"

t_token	*process_others(t_shell *prompt, t_token *token, t_counters *count)
{
	if (count->j > 0)
	{			
		token->data[count->j] = 0;
		token->next = malloc(sizeof(t_token));
		token = token->next;
		tok_init(token, prompt->size - count->i);
		count->j = 0;
	}
	return (token);
}

t_token	*new_token(t_shell *prompt, t_token *token, t_counters *count)
{
	token->data[0] = prompt->chtype;
	token->data[1] = 0;
	token->type = prompt->chtype;
	token->next = malloc(sizeof(t_token));
	token = token->next;
	tok_init(token, prompt->size - count->i);
	return (token);
}
