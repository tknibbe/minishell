#include <minishell.h>
#include <built_ins.h>

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
			write(1, " ", 1);
	}
	if (new_line)
		write(fd, "\n", 1);
	if (fd != 1)
		close(fd);
	return (0);
}
