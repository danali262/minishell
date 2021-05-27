#include "parser.h"

// void	print_tokens(t_token *tokens_list)         /* to be deleted */
// {
// 	t_token	*head;

// 	head = tokens_list;
// 	printf("tokens are:\n");
// 	while (head != NULL)
// 	{
// 		printf("|%s|\t|%d|\n", head->data, head->type);
// 		head = head->next;
// 	}
// }

static void	check_for_append(t_lexer_state *lex_state)
{
	t_token *head;
	t_token *temp;

	head = lex_state->tokens_list;
	while (head != NULL)
	{
		if (head->type == '>' && head->next->type == '>')
		{
			free(head->data);
			head->data = ft_strdup(">>");
			head->type = CHAR_APPEND;
			temp = head->next->next;
			head->next = temp;
			lex_state->tokens_nbr--;
		}
		else
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
	// printf("tokens with quotes:\n");
	// print_tokens(lex_state.tokens_list);        /* to be deleted */
	// printf("number of tokens is %d\n", lex_state.tokens_nbr);
	parser(&lex_state, shell);
	lexer_destroy(&lex_state);
	return (1);
}
