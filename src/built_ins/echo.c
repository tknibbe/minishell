
#include <minishell.h>
#include <built_ins.h>

/*echo function with -n option, if used will not print the new-line at the end
it will write all it's arguments seperated by a space*/
void	echo(char **echo)
{
	int		i;
	int		new_line;

	i = 1;
	free(echo[0]);
	if (!ft_strncmp(echo[i], "-n", 3))
	{
		free(echo[i++]);
		new_line = 1;
	}
	else
		new_line = 0;
	while (echo[i])
	{
		write(1, echo[i], ft_strlen(echo[i]));
		free(echo[i++]);
		if (echo[i])
			write(1, " ", 1);
	}
	free(echo);
	if (!new_line)
		write(1, "\n", 1);
}
