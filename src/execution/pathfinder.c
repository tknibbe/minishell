/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 12:43:08 by tknibbe           #+#    #+#             */
/*   Updated: 2023/08/29 13:43:20 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	append_cmd_path(t_ally *all, t_str *cmd)
{	
	char	**path;
	char	*cmd_path;
	char 	*full_path;
	int		i;

	if (access(cmd->str, X_OK) == 0)
	{
		return ;
	}
	path = ft_split(get_env("PATH", all->env), ':');
	cmd_path = ft_strjoin("/", cmd->str);
	i = 0;
	while(path[i])
	{
		full_path = ft_strjoin(path[i], cmd_path);
		if (access(full_path, X_OK) == 0)
		{
			free(cmd->str);
			cmd->str = full_path;
			break ;
		}
		i++;
	}
	if (!path[i])
	{
		printf("\nCOMMAND NOT FOUND (update in pathfinder.c when the pathfinder is added in the childprocess)\n");
		//ft_minishell_error(cmd->str, NULL, "command not found", 127);
	}
	free_dp(path);
	free(cmd_path);
}