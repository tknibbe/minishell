#include <minishell.h>
#include <parsing.h>
#include <built_ins.h>
#include <expansion.h>

static char	*expand(char *str, t_env *e)
{
	int	start;
	int	end;

	start = 0;
	while (str[start] && str[start - 1] != '$')
		start++;
	end = start;
	while (!ft_iswhitespace(str[end]) && str[end])
		end++;
	while (e)
	{
		if (!strncmp(&str[start], e->key, end - start))
		{
			free(str);
			return (ft_strjoin(e->value, "\n"));
		}
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

int	do_heredoc_or_so(t_rdr *r, t_env *e)
{
	int		fd;
	int		error;
	t_str	*heredoc;

	fd = open("/tmp/unieke_naam2", O_CREAT | O_RDWR | O_EXCL, 0644);
	if (fd < 0)
		ft_minishell_error("open()", "\"/tmp/unieke_naam2\"", \
			strerror(errno), errno);
	error = unlink("/tmp/unieke_naam2");
	if (error < 0)
		ft_minishell_error("unlink()", NULL, strerror(errno), errno);
	heredoc = r->file;
	if (r->type == HEREDOC)
		heredoc_expand(heredoc, e);
	while (heredoc)
	{
		printf("writing [%s] to file\n", heredoc->str);
		write(fd, heredoc->str, ft_strlen(heredoc->str));
		heredoc = heredoc->next;
	}
	return (fd);
}

void	open_file_and_dup(char *file, int flag, int to_dup, int permission)
{
	int	fd;

	fd = open(file, flag, permission);
	if (fd < 0)
		ft_minishell_error(NULL, file, strerror(errno), errno);
	if (dup2(fd, to_dup) < 0)
		ft_minishell_error("dup2()", NULL, strerror(errno), errno);
}

void	redirect(t_rdr *r, t_env_info *e)
{
	char	**file;

	while (r)
	{
		if (r->type == HEREDOC || r->type == HEREDOC_NO_EXP)
		{
			do_heredoc_or_so(r, e->head);
			r = r->next;
			continue ;
		}
		file = full_expansion(r->file, e);
		if (!(*file) || (*file && *(file + 1)))
			ft_minishell_error("ambiguous redirect", "expansion results in multiple or no arguments", NULL, 1);
		if (r->type == REDIRLEFT)
			open_file_and_dup(*file, O_RDONLY, STDIN_FILENO, 0);
		else if (r->type == REDIRRIGHT)
			open_file_and_dup(*file, O_WRONLY | O_CREAT | O_TRUNC, STDOUT_FILENO, 420);
		else if (r->type == APPEND)
			open_file_and_dup(*file,O_WRONLY | O_CREAT | O_APPEND, STDOUT_FILENO, 420);
		r = r->next;
	}
}
