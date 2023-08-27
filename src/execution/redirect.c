#include <minishell.h>
#include <parsing.h>
#include <built_ins.h>

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
			printf("do here doc and continue or so\n");
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
