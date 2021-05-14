#include "executor.h"

#include "builtins/builtins.h"

#include "libft.h"

#include <unistd.h>
#include <sys/wait.h>


int	run_child_process(t_lexer *lexerbuf) //lexerbuf changed for parser
{
	int	builtin_result;
	extern char **environ;

	char    *argv[2]; //it's hardcoded now, will need to add the functionality looking for the PATH
    argv[0] = "/bin/ls";
	argv[1] = NULL;
	
	builtin_result = can_execute_builtin(lexerbuf);
	if (builtin_result == -1) //if any error happened
	{
		// some error code?
			printf("builtin error\n"); //remove
		exit(1);
	}
	else if (builtin_result == 0) //if it's not a builtin
	{
		// if (PATH / command is found)
		// {
		int returnval = execve(argv[0], argv, environ);
			if (returnval == -1)
				ft_putstr_fd("execve error.\n", STDOUT_FILENO);	
			printf("executed\n"); //remove
			exit(0);
		// }
		// else
		// printf("bash: %s: command not found\n", lexerbuf->tokens_list->data); // print this line only if the command is nether in builtin nor in 
	}
	exit(0);
}

int	execute_command(t_lexer *lexerbuf) // argument will be changed
{
	pid_t pid;
	int status;


	if (lexerbuf->tokens_nbr == 0) // will be replaced by number of commands in parser
		return (1);
		//creating a child process:
	else
		// get number of commands & start executing one by one while the num of commands is reached: 
		
		// int interator = 0;
		// while (interator < numer_commands)
	// {
	// 	
	// }
		pid = fork();
	if (pid < 0)
	{
		ft_putstr_fd("Error. Unable to create the child process.\n", STDOUT_FILENO);
		exit(0);
	}
	else if (pid == 0)
	{
		if (!run_child_process(lexerbuf))
			return (0); // exit on process completion?
		exit(1);
	}
	else
	{
		if (!WIFEXITED(status))
		{
			if (wait(&status) != pid)
				ft_putstr_fd("Wait error.\n", STDOUT_FILENO);	
		}
		return (1);
	}
}
