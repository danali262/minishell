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
t_treenode	*cmd4(t_curtok *curtok);
t_treenode	*simplecmd(t_curtok *curtok);
t_treenode	*tokenlist(t_curtok *curtok);
t_treenode	*tokenlist1(t_curtok *curtok);
t_treenode	*tokenlist2(void);

void		delete_node(t_treenode **node);
void		set_node_data_type(t_treenode *node, char *data,
				t_nodetype nodetype);
void		attach_tree_branch(t_treenode *root, t_treenode *leftNode,
				t_treenode *rightNode);

char		*strip_quotes(char *arg, t_treenode *node);
int			handle_vars_and_args(char *arg);
char		*create_arg(char *arg, t_treenode *node);

t_treenode	*redirection_create_root(t_treenode *root, t_treenode *simplecmd,
				char *filename, int opt);
void		handle_node_arg(t_treenode *root, t_treenode *tokenlist, char *arg);
void		handle_node_var(t_treenode *root, t_treenode *tokenlist, char *arg);
void		handle_both_nodes(t_treenode *root, char *arg);

void		parser_error(t_treenode *node);

void		print_tree(t_treenode *node);

#endif
