#include <built_ins.h>
#include <minishell.h>
#include <readline/history.h>

char	*oldpwd(t_env_info *e, int fd)
{
	char	*nav;

	nav = get_env("OLDPWD", e);
	if (!nav || !*nav)
	{
		ft_minishell_error("cd", "OLDPWD", "not set", 0);
		return (NULL);
	}
	write(fd, nav, ft_strlen(nav));
	write(fd, "\n", 1);
	return (nav);
}

char	*get_nav(char *input, t_env_info *e, int fd)
{
	char	*nav;

	if (!input)
	{
		nav = get_env("HOME", e);
		if (!nav)
			ft_minishell_error("cd", "HOME", "not set", 0);
	}
	else if (!ft_strncmp("-", input, 2))
		nav = oldpwd(e, fd);
	else
	{
		nav = ft_strdup(input);
		if (!nav)
			ft_minishell_error("malloc()", NULL, strerror(errno), errno);
	}
	return (nav);
}

/*
	will try and change its current working directory
	to the first argument given
	if no argument is given it will navigate to the HOME directory
	specified in the environment
*/
int	cd(char **cmd, t_env_info *e, int fd)
{
	int		ret;
	char	*nav;

	ret = 0;
	nav = get_nav(cmd[1], e, fd);
	if (!nav)
	{
		if (fd != 1)
			close((fd));
		return (1);
	}
	if (chdir(nav) < 0)
		ret = ft_minishell_error("cd", nav, strerror(errno), 0);
	else
		update_var(e);
	if (fd != 1)
		close((fd));
	return (free(nav), ret);
}

/*
	will add the input to the readline history
	if no input is given it will skip this step
*/
int	history(char *s)
{
	if (s && *s)
		add_history(s);
	return (0);
}

/*
	will print the current working directory
	followed by a new line
*/
int	pwd(int fd)
{
	char	*buff;

	buff = getcwd(NULL, 0);
	if (!buff)
		return (ft_minishell_error("getcwd()", strerror(errno), NULL, errno));
	write(fd, buff, ft_strlen(buff));
	write(fd, "\n", 1);
	free(buff);
	if (fd != 1)
		close(fd);
	return (0);
}
