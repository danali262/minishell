#ifndef ENVIRONMENT
# define ENVIRONMENT

typedef struct s_envlist
{
	char				*name;
	char				*value;
	struct s_envlist	*next;
}				t_envlist;

#endif