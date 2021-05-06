#include "parser.h"

bool	term(int tokentype, char **buffer, t_curtok *curtok)
{
	if (curtok->current_token == NULL)
        return (false);
    if (curtok->current_token->type == tokentype)
    {
        if (buffer != NULL)
        {
            *buffer = malloc(ft_strlen(curtok->current_token->data) + 1);
            ft_strlcpy(*buffer, curtok->current_token->data, ft_strlen(curtok->current_token->data) + 1);
        }
        curtok->current_token = curtok->current_token->next;
        return (true);
    }
    curtok->current_token = curtok->current_token->next;
    return (false);
}