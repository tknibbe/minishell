/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 12:43:08 by tknibbe           #+#    #+#             */
/*   Updated: 2023/10/21 15:43:11 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*test_for_valid_path(char **path, char *cmd_path, char *cmd)
{
	int		i;
	char	*full_path;

	i = 0;
	while (path[i])
	{
		full_path = ft_strjoin(path[i], cmd_path);
		if (access(full_path, X_OK) == 0)
		{
			free(cmd);
			free_dp(path);
			free(cmd_path);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	return (NULL);
}

char	*append_cmd_path(t_env_info *env, char *cmd)
{
	char	**path;
	char	*cmd_path;
	char	*full_path;
	char	*temp;

	if (access(cmd, X_OK) == 0)
		return (cmd);
	temp = get_env("PATH", env);
	if (!temp)
		ft_minishell_error(cmd, NULL, "command not found", 127);
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
