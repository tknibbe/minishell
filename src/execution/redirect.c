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

static void	open_file_and_dup(char *file, int flag, int to_dup, int permission)
{
	int	fd;

	fd = open(file, flag, permission);
	if (fd < 0)
		ft_minishell_error(NULL, file, strerror(errno), 1);
	if (dup2(fd, to_dup) < 0)
		ft_minishell_error("dup2()", NULL, strerror(errno), errno);
}

int	redirect(t_rdr *r, t_env_info *e, int in, int out, int hierdok_num)
{
	char	**file;
	int		ret;

	ret = 0;
	while (r)
	{
		if ((r->type == HEREDOC_EXP || r->type == HEREDOC_NO_EXP))
		{
			do_heredoc_or_so(r, e, hierdok_num, in);
			r = r->next;
			continue ;
		}
		if (r->type == REDIRRIGHT || r->type == APPEND)
			ret = 1;
		file = full_expansion(r->file, e);
		if (!(*file) || (*file && *(file + 1)))
			ft_minishell_error("ambiguous redirect", "expansion results in multiple or no arguments", NULL, 1);
		if (r->type == REDIRLEFT && in != -1)
			open_file_and_dup(*file, O_RDONLY, in, 0);
		else if (r->type == REDIRRIGHT)
			open_file_and_dup(*file, O_WRONLY | O_CREAT | O_TRUNC, out, 420);
		else if (r->type == APPEND)
			open_file_and_dup(*file,O_WRONLY | O_CREAT | O_APPEND, out, 420);
		free_dp(file);
		r = r->next;
	}
	return (ret);
}
