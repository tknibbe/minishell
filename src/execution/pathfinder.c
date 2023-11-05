/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 12:43:08 by tknibbe           #+#    #+#             */
/*   Updated: 2023/11/04 16:55:41 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/stat.h>

char *check_validity(char *cmd)
{
	struct stat path;

	if (!stat(cmd, &path))
		if (access(cmd, X_OK | R_OK) != 0)
			ft_minishell_error(cmd, "Permission denied", NULL, 126);
	return (cmd);
}

static char	*test_for_valid_path(char **path, char *cmd_path, char *cmd)
{
	int		i;
	char	*full_path;

	i = 0;
	while (path[i])
	{
		full_path = ft_strjoin(path[i], cmd_path);
		if (!access(full_path, F_OK))
		{
			free(cmd);
			free_dp(path);
			free(cmd_path);
			return (check_validity(full_path));
		}
		free(full_path);
		i++;
	}
	return (NULL);
}

static char *check_local(char *cmd)
{
	struct stat path;
	
	if (EXIT_SUCCESS == stat(cmd, &path))
	{
		if (S_ISDIR(path.st_mode))
			ft_minishell_error(cmd, "Is a directory", NULL, 126);
		if (access(cmd, X_OK | R_OK | W_OK))
			ft_minishell_error(cmd, "Permission denied", NULL, 126);
	}
	else
		ft_minishell_error(cmd, "No such file or directory", NULL, 127);
	return (cmd);
}

char	*append_cmd_path(t_env_info *env, char *cmd)
{
	char	**path;
	char	*cmd_path;
	char	*full_path;
	char	*temp;

	if (!*cmd)
		ft_minishell_error("''", NULL, "command not found", 127);
	if (ft_strnstr(cmd, "/", ft_strlen(cmd)))
		return (check_local(cmd));
	temp = get_env("PATH", env);
	if (!temp)
		ft_minishell_error(cmd, NULL, "no such file or directory", 127);
	path = ft_split(temp, ':');
	if (!path)
		ft_minishell_error("malloc()", NULL, strerror(errno), errno);
	free(temp);
	cmd_path = ft_strjoin("/", cmd);
	if (!cmd_path)
		ft_minishell_error("malloc()", NULL, strerror(errno), errno);
	full_path = test_for_valid_path(path, cmd_path, cmd);
	if (full_path)
		return (full_path);
	ft_minishell_error(cmd, NULL, "command not found", 127);
	return (NULL);
}
