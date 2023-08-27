#include <minishell.h>
#include <expansion.h>
#include <built_ins.h>
#include <parsing.h>

	// big loop that loops through all conditionals
		// we can ignore token and input so best to free and set to null as soon as possible
		// after execution depending of the and_or variable continue or not
		// we store latest exit number ^
		// t_list = next
	// for every big loop we need a pipeline executor
		// set up pipes redirects
		// then check for subshell and cmd
	// the expanding happens always in the childprocess

#define OR 0
#define AND 1

t_list	*next_pipe_line(t_list *current)
{
	printf("free current node");
	if (!current->next)
		return (NULL);
	if (!(!current->exit_code && current->and_or || current->exit_code && !current->and_or))
	{
		printf(", and next node\n");
		return (current->next->next);
	}
	printf("\n");
	return (current->next);
}

void	set_pipe(int *p)
{
	if (pipe(p) < 0)
		ft_minishell_error("pipe()", strerror(errno), NULL, errno);
}

void	execute_child(t_exec *exec, int *p, int fd, t_env_info *e, char **cmd)
{
	if (p)
	{
		close(p[0]);
		dup2(p[1], STDOUT_FILENO);
		close(p[1]);
	}
	if (fd)
	{
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	if (exec->rdr)
		redirect(exec->rdr, e);
	if (cmd)
	{
		if (find_path(*cmd))
			ft_minishell_error(NULL, *cmd, "command not found", 127);
		get_environment_for_exec(e);
		execve(*cmd, cmd, e->env);
		printf("execve went wrong!\n");
		exit(1);
	}
	else if (exec->subshell)
		executor(exec->subshell, e);
	exit(0);
}

// int	execute_parent()

int	exec_pipe_line(t_exec *exec, t_env_info *e)
{
	int		p[2];
	int		fd;
	pid_t	pid;
	char	**cmd;

	fd = 0;
	while (exec)
	{
		cmd = NULL;
		if (exec->cmd)
			cmd = full_expansion(exec->cmd, e);
		if (cmd && !builtin(*cmd))
		{
			set_pipe(p);
			pid = fork();
			if (pid < 0)
				ft_minishell_error("fork()", strerror(errno), NULL, errno);
			else if (!pid)
				execute_child(exec, p, fd, e, cmd);
			fd = dup(p[0]);
			close(p[0]);
			close(p[1]);
		}
		exec = exec->next;
	}
	int status;
	waitpid(pid, &status, NULL);
	while (wait(NULL) != -1)
		;
}

void	executor(t_list *pipe_line, t_env_info *e)
{
	while (pipe_line)
	{
		printf("free and nullify token and input variable.\n");
		pipe_line->exit_code = exec_pipe_line(pipe_line->exec, e);
		pipe_line = next_pipeline(pipe_line);
	}
}
