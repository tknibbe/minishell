
# include "minishell.h"

int	ft_iswhitespace(int c)
{
	return (c == 32 || (c >= 9 && c <= 13));
}

int	ft_isname(int c)
{
	return ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') \
			|| (c >= 'A' && c <= 'Z') || c == '_');
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

/*Description:
This function is used to report errors. It prints an error message to the
standard error stream (file descriptor 2) with optional information such as
the program name, argument, and a description. The function can also exit the
program with a specified exit code if required.

Parameters:

    char *program: The name of the program that encountered the error.
    char *arg: An argument or specific context related to the error.
    char *desc: A description of the error.
    int ex: The exit code to be used if the function decides to exit the program.

Return Value:

    1 is returned after printing the error message. If the ex parameter is
	nonzero, the function may also exit the program.*/
int	ft_minishell_error(char *program, char *arg, char *desc, int ex)
{
	write(STDERR_FILENO, "minishell", 9);
	if (program)
	{
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, program, ft_strlen(program));
	}
	if (arg)
	{
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, arg, ft_strlen(arg));
	}
	if (desc)
	{
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, desc, ft_strlen(desc));
	}
	write(STDERR_FILENO, "\n", 1);
	if (ex)
		exit(ex);
	return (1);
}
