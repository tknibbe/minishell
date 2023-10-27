#include <minishell.h>
#include <parsing.h>
#include <built_ins.h>
#include <expansion.h>

static char	*expand(char *str, t_env *e) //wtf fix dit G
{
	int	start;
	int	end;

	start = 0;
	while (str[start] && str[start - 1] != '$')
		start++;
	end = start;
	while (ft_isname(str[end]) && str[end])
		end++;
	while (e)
	{
		if (!strncmp(&str[start], e->key, end - start))
			return (free(str), ft_strjoin(e->value, "\n"));
		e = e->next;
	}
	free(str);
	str = malloc(sizeof(char) * 2);
	if (!str)
		ft_minishell_error("malloc()", NULL, strerror(errno), errno);
	str[0] = '\n';
	str[1] = '\0';
	return (str);
}

void	heredoc_expand(t_str *heredoc, t_env *e)
{
	t_str	*temp;

	temp = heredoc;
	while (temp)
	{
		if (ft_strchr(temp->str, '$'))
			temp->str = expand(temp->str, e);
		temp = temp->next;
	}
}

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

void	do_heredoc_or_so(t_rdr *r, t_env *e, int hierdok_num, int in)
{
	int		fd;
	t_str	*heredoc;
	char	*filename;

	filename = getfilename(hierdok_num);
	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		ft_minishell_error("open()", filename, strerror(errno), errno);
	heredoc = r->file;
	if (r->type == HEREDOC)
		heredoc_expand(heredoc, e);
	while (heredoc)
	{
		write(fd, heredoc->str, ft_strlen(heredoc->str));
		heredoc = heredoc->next;
	}
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
		if ((r->type == HEREDOC || r->type == HEREDOC_NO_EXP))
			do_heredoc_or_so(r, e->head, hierdok_num, in);
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
