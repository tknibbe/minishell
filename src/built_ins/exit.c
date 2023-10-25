#include <minishell.h>

void	ms_exit(char **cmd)
{
	int	i;

	if (isatty(STDIN_FILENO))
		write(STDERR_FILENO, "exit\n", 5);
	if (!cmd[1])
		exit(0);
	i = 0;
	if (cmd[1][i] == '-' || cmd[1][i] == '+')
		i++;
	while (cmd[1][i] >= '0' && cmd[1][i] <= '9')
		i++;
	if (cmd[1][i])
		ft_minishell_error("exit()", cmd[1], "numeric argument required", 2);
	exit(ft_atoi(cmd[1]));
}
