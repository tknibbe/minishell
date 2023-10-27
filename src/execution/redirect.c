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


#include <minishell.h>
#include <parsing.h>
#include <built_ins.h>
#include <expansion.h>




char	*getfilename(int num)
{
	char	*nbr;
	char	*filename;

	nbr = ft_itoa(num);
	if (!nbr)
		ft_minishell_error("malloc()", NULL, strerror(errno), errno);
	filename = ft_strjoin("/tmp/unieke_naam", nbr);
	if (!filename)
		ft_minishell_error("malloc()", NULL, strerror(errno), errno);
	free(nbr);
	return (filename);
}

void	do_heredoc_or_so(t_rdr *r, t_env_info *e, int hierdok_num, int in)
{
	int		fd;
	t_str	*heredoc;
	char	*filename;

	filename = getfilename(hierdok_num);
	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		ft_minishell_error("open()", filename, strerror(errno), errno);
	heredoc = r->file;
	heredoc_write(heredoc, e, fd, r->type);
	close(fd);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		ft_minishell_error("open()", filename, strerror(errno), errno);
	if (dup2(fd, in) < 0)
		ft_minishell_error("dup2()", "duplicating heredoc", strerror(errno), errno);
	close(fd);
	if (unlink(filename))
		ft_minishell_error("unlink()", NULL, strerror(errno), errno);
	free(filename);
}

void	open_file_and_dup(char *file, int flag, int to_dup, int permission)
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
		if (r->type == REDIRRIGHT || r->type == APPEND)
			ret = 1;
		if ((r->type == HEREDOC_EXP || r->type == HEREDOC_NO_EXP))
			do_heredoc_or_so(r, e, hierdok_num, in);
		else // fix for heredoccie
		{
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
		}
		r = r->next;
	}
	return (ret);
}
