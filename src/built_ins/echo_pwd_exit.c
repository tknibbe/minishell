
#include "minishell.h"

/*
	echo function will write it's arguments to the standard output
	seperated by a space.
	if -n option is supplied at the start of it's argument, newline will be skipped
	otherwise it will end sentence with a newline
*/
int	echo(char **cmd, int fd)
{
	int		i;
	int		new_line;

	i = 1;
	new_line = 1;
	while (!ft_strncmp(cmd[i], "-n", 3))
	{
		i++;
		new_line = 0;
	}
	while (cmd[i])
	{
		write(fd, cmd[i], ft_strlen(cmd[i]));
		if (cmd[++i])
			write(fd, " ", 1);
	}
	if (new_line)
		write(fd, "\n", 1);
	if (fd != 1)
		close(fd);
	return (0);
}

int	ms_exit(char **cmd)
{
	int	i;

	i = 0;
	if (isatty(STDIN_FILENO))
		write(STDERR_FILENO, "exit\n", 5);
	while (cmd[i])
		i++;
	if (i > 2)
		return (ft_minishell_error("Minishell", "exit()", "too many arguments", 1));
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
	return (EXIT_SUCCESS);
}

/*
	will print the current working directory
	followed by a new line
*/
int	pwd(int fd)
{
	char	*buff;

	buff = getcwd(NULL, 0);
	if (!buff)
		return (ft_minishell_error("getcwd()", strerror(errno), NULL, errno));
	write(fd, buff, ft_strlen(buff));
	write(fd, "\n", 1);
	free(buff);
	if (fd != 1)
		close(fd);
	return (0);
}
