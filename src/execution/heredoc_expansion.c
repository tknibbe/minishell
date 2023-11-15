/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expansion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 16:13:53 by tymonknibbe       #+#    #+#             */
/*   Updated: 2023/11/15 12:33:16 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*getfilename(int num)
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

static void	write_expand(char *str, t_env_info *e, int fd)
{
	int		i;
	int		start;
	char	*var;

	i = 0;
	while (str[i])
	{
		start = i;
		while (str[i] && str[i] != '$')
			i++;
		write(fd, str + start, i - start);
		if (str[i] == '$')
		{
			var = get_env(&str[++i], e);
			if (str[i] == '?')
				i++;
			else
				while (ft_isname(str[i]))
					i++;
			if (var)
				write(fd, var, ft_strlen(var));
			free(var);
		}
	}
}

static void	heredoc_write(t_str *str, t_env_info *e, int fd, int type)
{
	while (str)
	{
		if (type == HEREDOC_NO_EXP)
			write(fd, str->str, ft_strlen(str->str));
		else
			write_expand(str->str, e, fd);
		str = str->next;
	}
}

void	do_heredoc_or_so(t_rdr *r, t_env_info *e, int hierdok_num, int in)
{
	int		fd;
	char	*filename;

	if (in == -1)
		return ;
	filename = getfilename(hierdok_num);
	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		ft_minishell_error("open()", filename, strerror(errno), errno);
	heredoc_write(r->file, e, fd, r->type);
	close(fd);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		ft_minishell_error("open()", filename, strerror(errno), errno);
	if (dup2(fd, in) < 0)
		ft_minishell_error("dup2()", "duplicating heredoc", \
			strerror(errno), errno);
	close(fd);
	if (unlink(filename))
		ft_minishell_error("unlink()", NULL, strerror(errno), errno);
	free(filename);
}
