#include "../shell_state.h"

void	initialize_shell(t_shell *shell)
{
    shell->nbr_pipes = 0;
    shell->nbr_semis = 0;
}