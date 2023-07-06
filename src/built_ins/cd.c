#include <minishell.h>

void	cd(char **path)
{
	if (path[1])
		chdir(path[1]);
	
}

void	pwd(void)
{
	char	buff[100];
	char	*p;
}