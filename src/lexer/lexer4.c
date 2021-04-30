#include "minishell.h"

t_token	*process_dquote_state(t_shell *prompt, t_token *token, t_counters
*count)
{
	token->data[count->j++] = prompt->cmd[count->i];
	if (prompt->chtype == CHAR_DQUOTE)
		prompt->state = STATE_GENERAL;
	return (token);
}

t_token	*process_quote_state(t_shell *prompt, t_token *token, t_counters *count)
{
	token->data[count->j++] = prompt->cmd[count->i];
	if (prompt->chtype == CHAR_QUOTE)
		prompt->state = STATE_GENERAL;
	return (token);
}
