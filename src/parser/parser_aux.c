#include "lexer/lexer.h"
#include "parser.h"
#include "../shell_utilities.h"

void	check_for_append(t_lexer_state *lex_state)
{
	t_token	*head;
	t_token	*temp;

	head = lex_state->tokens_list;
	while (head != NULL)
	{
		if (head->type == '>' && head->next->type == '>')
		{
			free(head->data);
			head->data = ft_strdup(">>");
			head->type = CHAR_APPEND;
			temp = head->next->next;
			free_token(head->next);
			head->next = temp;
			lex_state->tokens_nbr--;
		}
		else
			head = head->next;
	}
}

void	check_for_rhombus(t_lexer_state *lex_state)
{
	t_token	*head;
	t_token	*temp;

	head = lex_state->tokens_list;
	while (head != NULL)
	{
		if (head->type == '<' && head->next->type == '>')
		{
			free(head->data);
			head->data = ft_strdup("<>");
			head->type = CHAR_RHOMBUS;
			temp = head->next->next;
			head->next = temp;
			lex_state->tokens_nbr--;
		}
		else
			head = head->next;
	}
}

static int	syntax_error(char *data)
{
	ft_putstr_fd("Syntax Error near: ", STDOUT_FILENO);
	ft_putstr_fd(data, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	return (258);
}

int	count_redir(t_lexer_state *lex_state, t_shell *shell)
{
	t_token	*head;
	int		flag;

	head = lex_state->tokens_list;
	while (head->type != CHAR_EMPTY)
	{
		flag = 0;
		if (is_redirect_type(head))
		{
			shell->redir->redir_nbr++;
			if (head->next->type == CHAR_WHITESPACE)
			{
				head = head->next;
				flag = 1;
			}
		}
		if (flag == 1 && is_redirect_type(head->next))
		{
			shell->exit_code = syntax_error(head->next->data);
			lexer_destroy(lex_state);
			return (-1);
		}
		head = head->next;
	}
	return (0);
}

bool	term(int tokentype, char **buffer, t_curtok *curtok, t_treenode *node)
{
	if (curtok->current_token == NULL)
		return (false);
	if ((curtok->current_token->type == tokentype) || (tokentype == CHAR_REDIR
			&& (curtok->current_token->type == CHAR_GREATER
				|| curtok->current_token->type == CHAR_LESSER
				|| curtok->current_token->type == CHAR_APPEND
				|| curtok->current_token->type == CHAR_RHOMBUS)))
	{
		if (buffer != NULL)
		{
			*buffer = malloc(ft_strlen(curtok->current_token->data) + 1);
			if (!*buffer)
				parser_error(node);
			ft_strlcpy(*buffer, curtok->current_token->data,
				ft_strlen(curtok->current_token->data) + 1);
		}
		curtok->current_token = curtok->current_token->next;
		return (true);
	}
	curtok->current_token = curtok->current_token->next;
	return (false);
}
