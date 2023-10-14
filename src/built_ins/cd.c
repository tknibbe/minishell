#include <built_ins.h>
#include <minishell.h>
#include <readline/history.h>

// old pwd becomes pwd else
// owd becomes pwd

void	update_var(t_env_info *e, char *new)
{
	t_env	*curr;
	t_env	*pwd;
	t_env	*oldpwd;

	curr = e->head;
	pwd = NULL;
	oldpwd = NULL;
	while (curr)
	{
		if (!ft_strncmp("PWD", curr->key, 4))
			pwd = curr;
		else if (!ft_strncmp("OLDPWD", curr->key, 7))
			oldpwd = curr;
		if (pwd && oldpwd)
			break ;
		curr = curr->next;
	}
	if (oldpwd && pwd)
	{
		free(oldpwd->value);
		oldpwd->value = pwd->value;
		pwd->value = new;
	}
	else
	{
		if (!oldpwd)
			env_addback(e->head, env_new())
	}
}
// void	update_var(t_env_info *e, char *pwd)
// {
// 	t_env	*env;
// 	char	*old;
// 	t_env	*oldpwd;

// 	env = e->head;
// 	old = NULL;
// 	oldpwd = NULL;
// 	while (env)
// 	{
// 		if (!ft_strncmp("PWD", env->key, 4))
// 		{
// 			old = env->value;
// 			env->value = getcwd(NULL, 0);
// 			if (!env->value)
// 				ft_minishell_error("getcwd()", strerror(errno), NULL, errno);
// 		}
// 		else if (!ft_strncmp("OLDPWD", env->key, 7))
// 			oldpwd = env;
// 		if (old && oldpwd)
// 			break ;
// 		env = env->next;
// 	}
// 	if (oldpwd)
// 	{
// 		free(oldpwd->value);
// 		oldpwd->value = old;
// 	}
// }

static int	use_env(t_env_info *e, char *var, int fd)
{
	char	*val;

	val = get_env(var, e);
	if (chdir(val) < 0)
		return (ft_minishell_error("cd", var, "not set", 0));
	update_var(e, var);
	if (!ft_strncmp("OLDPWD", var, 7))
		return (pwd(NULL, fd));
	return (0);
}

int	cd(char **cmd, t_env_info *e, int fd)
{
	if (!cmd[1])
		return (free_dp(cmd), use_env(e, "HOME", fd));
	else if (!ft_strncmp(cmd[1], "-", 2))
		return (free_dp(cmd), use_env(e, "OLDPWD", fd));
	else if (chdir(cmd[1]) < 0)
		return (free_dp(cmd), ft_minishell_error("cd", cmd[1], strerror(errno), 0));
	update_var(e, cmd[1]);
	return (free_dp(cmd), 0);
}

int		history(char *s)
{
	if (s && *s)
		add_history(s);
	return (0);
}

int	pwd(char **cmd, int fd)
{
	char	*buff;
	
	if (cmd)
		free_dp(cmd);
	buff = getcwd(NULL, 0);
	if (!buff)
		return (ft_minishell_error("getcwd()", strerror(errno), NULL, errno));
	write(fd, buff, ft_strlen(buff));
	write(fd, "\n", 1);
	free(buff);
	return (0);
}
