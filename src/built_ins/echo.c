
#include <minishell.h>
#include <built_ins.h>

/*echo function with -n option, if -n option is used new line character at the end will not be printed
it will write all it's arguments seperated by a space*/
int	echo(char **cmd, int fd)
{
	int		i;
	int		new_line;

	i = 1;
	new_line = 1;
	while (!ft_strncmp(cmd[i], "-n", 3))
		new_line = 0;
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
