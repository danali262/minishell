#include "parser.h"

void	print_tokens(t_token *tokens_list)         /* to be deleted */
{
	t_token	*head;

	head = tokens_list;
	printf("tokens are:\n");
	while (head != NULL)
	{
		printf("|%s|\t|%d|\n", head->data, head->type);
		head = head->next;
	}
}

static void	check_for_append(t_lexer_state *lex_state)
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

static void	check_for_rhombus(t_lexer_state *lex_state)
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

static int	count_redir(t_lexer_state *lex_state, t_shell *shell)
{
	t_token	*head;
	int		flag;

	head = lex_state->tokens_list;
	while (head->type != CHAR_EMPTY)
	{
		flag = 0;
		if (head->type == CHAR_GREATER || head->type == CHAR_LESSER
			|| head->type == CHAR_APPEND || head->type == CHAR_RHOMBUS)
		{
			shell->redir->redir_nbr++;
			if (head->next->type == CHAR_WHITESPACE)
			{
				head = head->next;
				flag = 1;
			}
		}
		if (flag == 1 && (head->next->type == CHAR_GREATER || head->next->type == CHAR_LESSER || head->next->type == CHAR_APPEND || head->next->type == CHAR_RHOMBUS))
		{
			ft_putstr_fd("Syntax Error near: ", STDOUT_FILENO);
			ft_putstr_fd(head->next->data, STDOUT_FILENO);
			ft_putstr_fd("\n", STDOUT_FILENO);
			shell->exit_code = 258;
			return (-1);
		}
		head = head->next;
	}
	return (0);
}

static void	remove_spaces(t_lexer_state *lex_state)
{
	t_token	*head;
	t_token *prev;
	t_token	*temp;

    prev = NULL;
	head = lex_state->tokens_list;
	temp = head;
	while (temp != NULL && temp->type == ' ')
	{
		head = temp->next;
		free_token(temp);
		temp = head;
	}
	while (temp != NULL)
	{
		while (temp != NULL && temp->type != ' ')
		{
			prev = temp;
			temp = temp->next;
		}
		if (temp == NULL)
			return;
		prev->next = temp->next;
		free_token(temp);
		temp = prev->next;
	}
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
	// printf("tokens with spaces:\n");
	// print_tokens(lex_state.tokens_list);        /* to be deleted */
	// printf("number of tokens is %d\n", lex_state.tokens_nbr);
	if (lexer_result == -1)
		return (-1);
	else if (lexer_result == 0)
		return (0);
	check_for_append(&lex_state);
	check_for_rhombus(&lex_state);
	if(count_redir(&lex_state, shell) == -1)
		return(0);
	remove_spaces(&lex_state);
	// printf("tokens without spaces:\n");
	// print_tokens(lex_state.tokens_list);        /* to be deleted */
	// printf("number of tokens is %d\n", lex_state.tokens_nbr);
	count_pipes(&lex_state, shell);
	if (parser(&lex_state, shell) == ERROR)
	{
		lexer_destroy(&lex_state);
		return (0);
	}
	lexer_destroy(&lex_state);
	return (1);
}
