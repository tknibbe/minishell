#include <minishell.h>
#include <stdlib.h>

int	ft_iswhitespace(int	c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}

int	ft_isname(int c)
{
	return ((c >= '0' && c <='9') || (c >= 'a' && c <='z') || (c >= 'A' && c <='Z') || c == '_');
}

int	ft_isinset(int c, char *s)
{
	while (*s)
	{
		if (*s == c)
			return (1);
		s++;
	}
	return (0);
}

int	ft_minishell_error(char *program, char *arg, char *desc, int ex)
{
	write(2, "minishell: ", 11);
	if (program)
		write(2, program, ft_strlen(program));
	if (arg)
	{
		write(2, ": ", 2);
		write(2, arg, ft_strlen(arg));
	}
	if (desc)
	{
		write(2, ": ", 2);
		write(2, desc, ft_strlen(desc));
	}
	write(2, "\n", 1);
	if (ex)
		exit(ex);
	return (1);
}
