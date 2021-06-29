#include "parser.h"
#include "../shell_utilities.h"

static void	remove_spaces_loop(t_token *temp, t_token *prev)
{
	while (temp != NULL)
	{
		while (temp != NULL && temp->type != ' ')
		{
			prev = temp;
			temp = temp->next;
		}
		if (temp == NULL)
			return ;
		prev->next = temp->next;
		free_token(temp);
		temp = prev->next;
	}
}

static void	remove_spaces(t_lexer_state *lex_state)
{
	t_token	*head;
	t_token	*prev;
	t_token	*temp;

	prev = NULL;
	head = lex_state->tokens_list;
	temp = head;
	while (temp != NULL && temp->type == ' ')
	{
		if (temp->next->type != ' ')
		{
			printf("am i here?\n");
			head = temp->next;
			free_token(temp);
			temp = head;
		}
	}
	remove_spaces_loop(temp, prev);
}

static void	count_pipes(t_lexer_state *lex_state, t_shell *shell)
{
	t_token	*head;

	head = lex_state->tokens_list;
	while (head != NULL)
	{
		if (head->type == CHAR_PIPE)
			shell->redir->pipes_nbr++;
		if (head->type == CHAR_SEMICOLON)
			shell->redir->semi_nbr++;
		head = head->next;
	}
}

int	parse_command_line(t_shell *shell)
{
	t_lexer_state	lex_state;
	int				lexer_result;

	lex_state.line = &shell->cmd_line;
	lexer_result = lexer_build(&lex_state);
	if (lexer_result == -1)
		return (-1);
	else if (lexer_result == 0)
		return (0);
	check_for_append(&lex_state);
	check_for_rhombus(&lex_state);
	if (count_redir(&lex_state, shell) == -1)
		return (0);
	remove_spaces(&lex_state);
	count_pipes(&lex_state, shell);
	if (parser(&lex_state, shell) == ERROR)
	{
		lexer_destroy(&lex_state);
		delete_node(&shell->syntax_tree);
		return (0);
	}
	lexer_destroy(&lex_state);
	return (1);
}
