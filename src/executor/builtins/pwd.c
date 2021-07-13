#include "builtins.h"
#include "../executor.h"

#include "libft.h"

#include <unistd.h>
#include <string.h>
#include <sys/errno.h>

/*
** bash doesn't care if there are any arguments after pwd,
** it ignores them and prints the current location
** we have also removed the check for too many arguments (like in zsh)
** or invalid option
** as our pwd is expected to work without options
*/

int	execute_pwd(t_treenode *simple_cmd_node, t_shell *shell)
{
	char	pwd_value[256];

	(void)simple_cmd_node;
	(void)shell;
	if (getcwd(pwd_value, sizeof(pwd_value)) == NULL)
		printf("pwd: %s\n\r", strerror(errno));
	printf("%s\n\r", pwd_value);
	return (SUCCESS);
}
