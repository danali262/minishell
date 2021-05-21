#include "../shell_state.h"

void    init_tree(t_treenode *syntax_tree)
{
    syntax_tree->data = NULL;
    syntax_tree->type = NODE_EMPTY;
    syntax_tree->left = NULL;
    syntax_tree->right = NULL;
}