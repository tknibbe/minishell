
#include <minishell.h>
#include <built_ins.h>

void	echo(char **echo)
{
	int		i;
	int		new_line;

	i = 0;
	new_line = 0;
	if (!ft_strncmp(echo[0], "-n", 3))
		new_line = ++i;
	while (echo[i])
	{
		write(1, echo[i], ft_strlen(echo[i]));
		if (echo[++i])
			write(1, " ", 1);
	}
	if (!new_line)
		write(1, "\n", 1);
}
