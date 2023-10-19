#include <built_ins.h>
#include <minishell.h>
#include <readline/history.h>

int	update_env(t_env_info *e, t_env *edit, char *s)
{
	
}

void	update_var(t_env_info *e)
{
	char	*pwd;
	t_env	*curr;
	t_env	*oldpwd;

	curr = e->head;
	pwd = NULL;
	oldpwd = NULL;
	while (curr)
	{
		if (!ft_strncmp("PWD", curr->key, 4))
		{
			pwd = curr->value;
			curr->value = getcwd(NULL, 0);
			if (!curr->value)
				ft_minishell_error("getcwd()", NULL, strerror(errno), errno);
			free(curr->joined_value);
			curr->joined_value = ft_envjoin(curr->key, curr->value);
			e->has_changed = 1;
		}
		else if (!ft_strncmp("OLDPWD", curr->key, 7))
			oldpwd = curr;
		if (pwd && oldpwd)
			break ;
		curr = curr->next;
	}
	if (oldpwd)
	{
		free(oldpwd->value);
		if (pwd)
			oldpwd->value = pwd;
		else
			oldpwd->value = ft_strdup("");
		if (!oldpwd->value)
			ft_minishell_error("malloc()", NULL, strerror(errno), errno);	
		free(oldpwd->joined_value);
		oldpwd->joined_value = ft_envjoin(oldpwd->key, oldpwd->value);
		e->has_changed = 1;
	}
	else
		free(pwd);
}

int	cd(char **cmd, t_env_info *e, int fd)
{
	int		ret;
	char	*nav;

	ret = 0;
	if (!cmd[1] || !ft_strncmp("-", cmd[1], 2))
	{
		if (!cmd[1])
			nav = get_env("HOME", e);
		else
			nav = get_env("OLDPWD", e);
		if (!nav && !cmd[1])
			return (free_dp(cmd), ft_minishell_error("cd", "HOME", "not set", 0));
		else if (!nav)
			return (free_dp(cmd), ft_minishell_error("cd", "OLDPWD", "not set", 0));
	}
	else
	{
		nav = ft_strdup(cmd[1]);
		if (!nav)
			return (ft_minishell_error("malloc()", NULL, strerror(errno), errno));
	}
	if (chdir(nav) < 0)
		ret = ft_minishell_error("cd", nav, strerror(errno), 0);
	update_var(e);
	return (free_dp(cmd), free(nav), ret);
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
