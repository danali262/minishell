#include "../shell_state.h"

void    init_tree(t_treenode *syntax_tree)
{
    syntax_tree->data = malloc(1);
    syntax_tree->data = NULL;
    syntax_tree->type = malloc(1);
    syntax_tree->type = NULL;
    syntax_tree->left = malloc(sizeof(t_treenode));
    syntax_tree->left = NULL;
    syntax_tree->right = malloc(sizeof(t_treenode));
    syntax_tree->right = NULL;
}