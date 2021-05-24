#include "parser.h"

void	parser_error(t_treenode *node)
{
	ft_putstr_fd("Malloc error in parser.\n", STDOUT_FILENO);
	delete_node(&node);
	exit(1);
}
