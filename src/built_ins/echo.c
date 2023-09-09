
#include <minishell.h>
#include <built_ins.h>

/*echo function with -n option, if used will not print the new-line at the end
it will write all it's arguments seperated by a space*/
void	echo(char **cmd)
{
	int		i;
	int		new_line;

	i = 1;
	free(cmd[0]);
	new_line = 0;
	while (!ft_strncmp(cmd[i], "-n", 3))
	{
		new_line = 1;
		free(cmd[i]);
		i++;
	}
	while (cmd[i])
	{
		write(1, cmd[i], ft_strlen(cmd[i]));
		free(cmd[i++]);
		if (cmd[i])
			write(1, " ", 1);
	}
	free(cmd);
	if (!new_line)
		write(STDERR_FILENO, "\n", 1);
}
