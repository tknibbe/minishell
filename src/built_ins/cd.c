/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 12:33:08 by tknibbe           #+#    #+#             */
/*   Updated: 2023/11/15 12:33:09 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	swap(t_env *pwd, t_env *oldpwd, t_env_info *e)
{
	if (!pwd)
	{
		pwd = env_new("PWD=");
		env_addback(&e->head, pwd);
		e->count++;
	}
	if (!oldpwd)
	{
		oldpwd = env_new("OLDPWD=");
		env_addback(&e->head, oldpwd);
		e->count++;
	}
	free(oldpwd->value);
	oldpwd->value = pwd->value;
	pwd->value = getcwd(NULL, 0);
	if (!pwd->value)
		return (ft_minishell_error("getcwd()", NULL, strerror(errno), 0));
	update_env(pwd, e);
	update_env(oldpwd, e);
	return (0);
}

static int	update_var(t_env_info *e)
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
	return (swap(pwd, oldpwd, e));
}

static char	*oldpwd(t_env_info *e, int fd)
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

static char	*get_nav(char *input, t_env_info *e, int fd)
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

	if (cmd[1] && cmd[2])
		return (ft_minishell_error("cd", NULL, "too many arguments", 0));
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
		ret = update_var(e);
	if (fd != 1)
		close((fd));
	return (free(nav), ret);
}
