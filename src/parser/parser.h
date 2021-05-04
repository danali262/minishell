#ifndef PARSER_H
# define PARSER_H

#include "lexer/lexer.h"
#include "../reader/command_line_state.h"
#include <stdbool.h>

typedef struct  s_treenode
{
	t_token					*current_token;
    int						type;
    char					*data;
	int						children;			/* number of children */
    struct	s_treenode		*left;				/* rename it to first child..? */
    struct	s_treenode		*right;
	struct	s_treenode		*next_sibling;		/* useful because there may be more than two child nodes..? */
	struct	s_treenode		*prev_sibling;
}               t_treenode;

typedef struct	s_curtok
{
	t_token	*current_token;
}				t_curtok;

typedef	enum
{
	NODE_SEMI,							/* ; */
	NODE_PIPE,							/* | */
	NODE_CMD,							/* simple command */
	NODE_REDIRECT_IN,					/* < */
	NODE_REDIRECT_OUT,					/* > */
	NODE_APPEND,						/* >> */
	NODE_ARG,							/* argument */
	NODE_PATH,							/* pathname */
	NODE_FILE							/* filename */
}		t_nodetype;


int			parse_command_line(t_line *cmd_line);
int			parser(t_lexer *lexerbuf, t_treenode *syntax_tree);

bool		term(int tokentype, char *buffer, t_token *current_token);
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

void		delete_node(t_treenode *node);
void		set_node_type(t_treenode *node, t_nodetype nodetype);
void		set_node_data(t_treenode *node, char *data);
void		attach_tree_branch(t_treenode *root, t_treenode *leftNode, t_treenode *rightNode);


// t_treenode	*new_node(t_nodetype type);
// void		free_node_tree(t_treenode *node);
// void		set_node_val_str(t_treenode *node, char *val);
// void		add_child_node(t_treenode *parent, t_treenode *child);

#endif
