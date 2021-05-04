#include "lexer/lexer.h"
#include "parser.h"

static t_treenode	*parse_simple_command(t_token *current_token)
{
	t_treenode	*cmd;
	t_treenode	*word;
	// t_token		*temp;

	if (!current_token)
		return (NULL);
	cmd = new_node(NODE_CMD);
	if (!cmd)
	{
		free_token(current_token);
		return (NULL);
	}
	// printf("new node is %s\n", cmd->data);
	while (current_token)
	{
		printf("currrent token is %s\n", current_token->data);
		word = new_node(NODE_ARG);
		if (!word)
		{
			free_node_tree(cmd);
			free_token(current_token);
			return (NULL);
		}
		set_node_val_str(word, current_token->data);
		add_child_node(cmd, word);
		// temp = current_token;
		current_token = current_token->next;
		// free_token(temp);
	}
	return (cmd);
}


// static t_treenode	*parser_functions(t_token *current_token, t_treenode *syntax_tree)
// {
// 	syntax_tree = parse_simple_command(current_token);
// 	printf("syntax tree is %s\n", syntax_tree->data);
// 	// printf("syntax tree child is %s\n", syntax_tree->left->data);
// 	// printf("syntax tree child's child is %s\n", syntax_tree->left->next_sibling->data);
// 	syntax_tree = syntax_tree->left;
// 	while (syntax_tree != NULL)
// 	{
// 		printf("syntax tree child is %s\n", syntax_tree->data);
// 		// printf("syntax tree child's child is %s\n", syntax_tree->left->data);
// 		syntax_tree = syntax_tree->next_sibling;
// 		// printf("syntax tree child is %s\n", syntax_tree->data);
// 	}
// 