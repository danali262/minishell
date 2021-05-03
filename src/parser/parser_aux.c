#include "parser.h"

bool	term(int tokentype, char *buffer, t_token *current_token)
{
	if (current_token == NULL)
        return (false);
    if (current_token->type == tokentype)
    {
        if (buffer != NULL)
        {
            buffer = malloc(ft_strlen(current_token->data) + 1);
            ft_strlcpy(buffer, current_token->data, ft_strlen(current_token->data) + 1);
        }
        current_token = current_token->next;
        return (true);
    }
    current_token = current_token->next;
    return (false);
}