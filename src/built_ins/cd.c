#include <minishell.h>

void	get_home(char **env)
{
	char	*home;

	home = get_env("HOME", env);
	if (!home)
	{
		write(2, "minishell: cd: HOME not set\n", 29);
		return ;
	}
	if (chdir(home) < 0)
		perror("minishell: cd");
	free(home);
}

void	cd(char *path, char **env)
{
	if (!path)
		return (get_home(env));
	if (!ft_strncmp(path, "~", 2))
		return (get_home(env));
	if (chdir(path) < 0)
		perror("minishell: cd");

	/*	maybe also set the last error number to 1
		and also send the environment so we can get the path */
}

void	history(const char *s)
{
	if (s && s[0])
		add_history(s);
}

void	pwd(void)
{
	char	*buff;

	buff = getcwd(NULL, 0);
	if (!buff)
		perror("minishell: pwd");
	printf("%s\n", buff);
	free(buff);
}
