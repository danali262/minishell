#ifndef PARSER_H
# define PARSER_H

# include "lexer/lexer.h"
# include "../reader/command_line_state.h"
# include "../shell_state.h"
# include <stdbool.h>

typedef struct s_curtok
{
	t_token	*current_token;
}				t_curtok;

bool		term(int tokentype, char **buffer, t_curtok *curtok,
				t_treenode *node);
void		initialize_syntax_tree(t_treenode *syntax_tree);

void		check_for_append(t_lexer_state *lex_state);
void		check_for_rhombus(t_lexer_state *lex_state);
int			count_redir(t_lexer_state *lex_state, t_shell *shell);

t_treenode	*command_line(t_curtok *curtok);
t_treenode	*command_line1(t_curtok *curtok);
t_treenode	*command_line2(t_curtok *curtok);
t_treenode	*command_line3(t_curtok *curtok);
t_treenode	*job(t_curtok *curtok);
t_treenode	*job1(t_curtok *curtok);
t_treenode	*job2(t_curtok *curtok);
t_treenode	*cmd(t_curtok *curtok);
t_treenode	*cmd1(t_curtok *curtok);
t_treenode	*cmd2(t_curtok *curtok);
t_treenode	*cmd3(t_curtok *curtok);
t_treenode	*simplecmd(t_curtok *curtok);
t_treenode	*tokenlist(t_curtok *curtok);
t_treenode	*tokenlist1(t_curtok *curtok);
t_treenode	*tokenlist2(void);
t_treenode	*redirlist(t_curtok *curtok);
t_treenode	*redirlist1(t_curtok *curtok);
t_treenode	*redirlist2(t_curtok *curtok);
t_treenode	*redirlist3(void);

void		delete_node(t_treenode **node);
void		set_node_data_type(t_treenode *node, char *data,
				t_nodetype nodetype);
void		attach_tree_branch(t_treenode *root, t_treenode *leftNode,
				t_treenode *rightNode);
t_treenode	*create_node(t_treenode *root, char *operator);
t_treenode	*handle_root_redirection(t_treenode *root, t_treenode
				*simplecmd, char *operator, char *filename);
t_treenode	*handle_root_redirection_multiple(t_treenode *root, t_treenode
				*node, char *operator, char *filename);
t_treenode	*handle_redirect_in_single(t_treenode *root, t_treenode *left_node,
				t_treenode *right_node, char *filename);
t_treenode	*handle_redirect_out_single(t_treenode *root, t_treenode *left_node,
				t_treenode *right_node, char *filename);
t_treenode	*handle_append_single(t_treenode *root, t_treenode *left_node,
				t_treenode *right_node, char *filename);
t_treenode	*handle_rhombus_single(t_treenode *root, t_treenode *left_node,
				t_treenode *right_node, char *filename);
t_treenode	*handle_redirect_in_multiple(t_treenode *root,
				t_treenode *left_node, t_treenode *right_node, char *filename);
t_treenode	*handle_redirect_out_multiple(t_treenode *root,
				t_treenode *left_node, t_treenode *right_node, char *filename);
t_treenode	*handle_append_multiple(t_treenode *root, t_treenode *left_node,
				t_treenode *right_node, char *filename);
t_treenode	*handle_rhombus_multiple(t_treenode *root, t_treenode *left_node,
				t_treenode *right_node, char *filename);

t_treenode	*multiple_redirection_create_root(t_treenode *root, t_treenode
				*right_node, char *filename, int opt);
t_treenode	*simple_redirection_create_root(t_treenode *root, t_treenode
				*simplecmdNode, char *filename, int opt);

void		parser_error(t_treenode *node);

void		print_tree(t_treenode *node);

#endif
