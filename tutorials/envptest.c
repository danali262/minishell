#include <stdio.h>

int main(int ac, char **av, char **envp)
{
    int i;

    printf("ac is %d\n", ac);
    i = 0;
    while (envp[i] != '\0')
    {
        printf("%s\n", envp[i]);
        i++;
    }
    return (0);
}