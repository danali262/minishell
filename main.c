#include "minishell.h"

// static char *read_input(char *cmd)
// {
//     char *buf;
//     int ret;
// 
//     ret = 1;
//     while (ret > 0)
//     {
//         buf = (char *)malloc(sizeof(char) * 1001);
//         ret = read(0, buf, 1000);
//         buf[ret] = '\0';
//         cmd = ft_strcat(cmd, buf);
//     }
//     return (cmd);
// }

static char *get_command(char *buf)
{
    char    **array;

    array = ft_split(buf, '\n');
    return(array[0]);
}

void    print_tokens(t_lexer *lexerbuf)
{
    t_token *head;

    head = lexerbuf->tokens_list;
    while (head != NULL)
    // while (head->next != NULL)
    {
        printf("%s\n", head->data);
        head = head->next;
    }
}

int		main(void)
// int     main(int ac, char **av, char **envp)
{
	t_shell     prompt;
	int         i;
    size_t		len;
    t_lexer		lexerbuf;

	prompt.buf = ft_strdup("");
	i = 0;
    while (1)
    {
		ft_putstr_fd("$ ", 1);		/* to be replaced with a more sophisticated command prompt */
		prompt.buf = read_input(prompt.buf);
		while (prompt.buf[i] != '\n')
			i++;
		if (prompt.buf[i] == '\n')
	   		break;
    }
    prompt.cmd = get_command(prompt.buf);
    len = ft_strlen(prompt.cmd);        /* without '/0' */
    lexer_build(prompt.cmd, &lexerbuf);
    print_tokens(&lexerbuf);
    return (0);
}
