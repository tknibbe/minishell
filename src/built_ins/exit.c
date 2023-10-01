#include <minishell.h>

int	ms_isnum(char c)
{
	return(c >= '0' && c <= '9');
}

int ms_exit(char **cmd)
{
	int	i;
	int	check;

	if (isatty(STDIN_FILENO))
		write(1, "exit\n", 5);
	if (!cmd[1])
		exit(0);
	check = 0;
	i = 0;
	if (cmd[1][i] == '-' || cmd[1][i] == '+')
		i++;
	while (cmd[1][i])
	{
		if (!ms_isnum(cmd[1][i]))
		{
			check = 1;
			break ;
		}
		i++;
	}
	if (check)
		ft_minishell_error("exit()", cmd[1], "numeric argument required", 2);
	exit(ft_atoi(cmd[1]));
	return (0);
}
