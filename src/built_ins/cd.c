#include <built_ins.h>
#include <minishell.h>
#include <readline/history.h>

static int	use_env(t_env_info *e, char *var)
{
	if (chdir(get_env(var, e)) < 0)
	{
		ft_minishell_error("cd", var, "not set");
		return (1);
	}
	return (0);
}

int	cd(char **cmd, t_env_info *e)
{
	if (!cmd[1])
		return (free_dp(cmd), use_env(e, "HOME"));
	else if (!ft_strncmp(cmd[1], "-", 2))
		return (free_dp(cmd), use_env(e, "OLDPWD"));
	else if (chdir(cmd[1]) < 0)
		return (free_dp(cmd), ft_minishell_error("cd", cmd[1], strerror(errno)));
	free_dp(cmd);
	return (0);
}

void	history(const char *s)
{
	if (s && s[0])
		add_history(s);
}

int	pwd(void)
{
	char	*buff;

	buff = getcwd(NULL, 0);
	if (!buff)
		return (ft_minishell_error("pwd", strerror(errno), NULL));
	printf("%s\n", buff);
	free(buff);
	return (0);
}
