#ifndef BUILTINS_MAP_H
# define BUILTINS_MAP_H

# include "../../parser/lexer/lexer.h"

typedef struct s_builtins_map
{
	char	*cmd_name;
	int		(*cmd_executor)(t_lexer *lexerbuf);
}				t_builtins_map;

#endif
