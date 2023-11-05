/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tymonknibbe <tymonknibbe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 15:12:03 by tymonknibbe       #+#    #+#             */
/*   Updated: 2023/10/27 17:48:26 by tymonknibbe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int	open_file_and_dup(char *file, int flag, int to_dup, int permission)
{
	int	fd;

	fd = open(file, flag, permission);
	if (to_dup >= 0 && to_dup <= 1 && fd < 0)
		ft_minishell_error(NULL, file, strerror(errno), 1);
	else if (fd < 0)
		return (ft_minishell_error(NULL, file, strerror(errno), 0));
	if ((to_dup == STDOUT_FILENO || to_dup == 3) && dup2(fd, to_dup) < 0)
		ft_minishell_error("dup2()", NULL, strerror(errno), errno);
	else if (to_dup == 4)
		close(4);
	return (0);
}

int	is_heredoc(t_rdr **r, t_env_info *e, int hierdok_num, int builtin)
{
	if ((*r)->type == HEREDOC_EXP || (*r)->type == HEREDOC_NO_EXP)
	{
		if (!builtin)
			do_heredoc_or_so(*r, e, hierdok_num, STDIN_FILENO);
		*r = (*r)->next;
		return (1);
	}
	return (0);
}

int	do_redirect(int type, char **file, int builtin)
{
	if (builtin)
	{
		if (!(*file) || *(file + 1))
			return (ft_minishell_error("ambiguous redirect", "expansion results in multiple or no arguments", NULL, 0));
		if (type == REDIRLEFT && open_file_and_dup(*file, O_RDONLY, 4, 0))
			return (1);
		else if (type == REDIRRIGHT && open_file_and_dup(*file, O_WRONLY | O_CREAT | O_TRUNC, 3, 420))
			return (1);
		else if (type == APPEND && open_file_and_dup(*file,O_WRONLY | O_CREAT | O_APPEND, 3, 420))
			return (1);
		if (type == REDIRRIGHT || type == APPEND)
			return (3);
		return (0);
	}
	if (!(*file) || *(file + 1))
		ft_minishell_error("ambiguous redirect", "expansion results in multiple or no arguments", NULL, 1);
	else if ((type == REDIRLEFT && open_file_and_dup(*file, O_RDONLY, STDIN_FILENO, 0)) || \
			(type == REDIRRIGHT && open_file_and_dup(*file, O_WRONLY | O_CREAT | O_TRUNC, STDOUT_FILENO, 420)) || \
			(type == APPEND && open_file_and_dup(*file,O_WRONLY | O_CREAT | O_APPEND, STDOUT_FILENO, 420)))
		return (1);
	return (0);
}

int	redirect(t_rdr *r, t_env_info *e, int hierdok_num, int builtin)
{
	char	**file;
	int		ret;

	ret = 0;
	while (r)
	{
		if (is_heredoc(&r, e, hierdok_num, builtin))
			continue ;
		file = full_expansion(r->file, e);
		ret = do_redirect(r->type, file, builtin);
		if (ret == 1)
			return (free_dp(file), 1);
		else if (ret == 3)
			ret = 3;
		free_dp(file);
		r = r->next;
	}
	return (ret);
}
