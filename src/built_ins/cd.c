#include <built_ins.h>
#include <minishell.h>
#include <readline/history.h>

void	builtin(t_env *env, char *key)
{
	char	*to_fetch;

	to_fetch = get_env(key, env);
	if (!to_fetch)
	{
		write(2, "minishell: cd: ", 16);
		write(2, key, ft_strlen(key));
		write(2, " not set\n", 10);
	}
	else if (chdir(to_fetch) < 0)
		perror("minishell: cd");
	free(to_fetch);
}

void	cd(char *path, t_env *env)
{
	if (!path || !ft_strncmp(path, "~", 2))
		builtin(env, "HOME");
	if (!ft_strncmp(path, "-", 2))
		builtin(env, "OLDPWD");
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
