#include "command_history_navigation.h"

#include <stdio.h>

// int main(int argc, char **argv, char **envp)
int main(int argc, char **argv)
{
    if (argc && argv)
    {

    }
    extern char **environ;
    int i = 0;
    while (environ[i] != NULL)
    {
        printf("%s\n", environ[i]);
        i++;
    }
    init_terminal_data();
    return (0);
}