#ifndef PARSER_H
# define PARSER_H

#include "lexer/lexer.h"
#include "../reader/command_line_state.h"
#include "../shell_state.h"
#include <stdbool.h>

typedef struct	s_curtok
{
	t_token	*current_token;
}				t_curtok;

typedef	enum
{
	NODE_SEMI,							/* 0. ; */
	NODE_PIPE,							/* 1. | */
	NODE_CMD,							/* 2. simple command */
	NODE_REDIRECT_IN,					/* 3. < */
	NODE_REDIRECT_OUT,					/* 4. > */
	NODE_APPEND,						/* 5. >> */
	NODE_FILE,							/* 6. filename */
	NODE_PATH,							/* 7. pathname */
	NODE_ARG,							/* 8. argument */
	NODE_TOKEN,							/* 9. tokenlist */
	NODE_EMPTY							/* 10. empty */
}		t_nodetype;

bool	term(int tokentype, char **buffer, t_curtok *curtok);
void    initialize_syntax_tree(t_treenode *syntax_tree);

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

void	delete_node(t_treenode *node);
void	set_node_data_type(t_treenode *node, char *data, t_nodetype nodetype);
void	attach_tree_branch(t_treenode *root, t_treenode *leftNode, t_treenode *rightNode);

void	print_tree(t_treenode *node);

#endif