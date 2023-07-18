#include <built_ins.h>
#include <minishell.h>
#include <readline/history.h>

void	get_home(t_env *env)
{
	char	*home;

	home = get_env("HOME", env);
	if (!home) 
		write(2, "minishell: cd: HOME not set\n", 29);
	else if (chdir(home) < 0)
		perror("minishell: cd");
}

void	cd(char *path, t_env *env)
{
	if (!path || !ft_strncmp(path, "~", 2))
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
