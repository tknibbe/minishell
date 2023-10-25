#include <minishell.h>
#include <exec.h>

void	execute_child(t_exec *exec, t_env_info *e, t_process *proc)
{
	if (proc->p)
	{
		close(proc->p[0]);
		dup2(proc->p[1], STDOUT_FILENO);
		close(proc->p[1]);
	}
	if (proc->fd)
	{
		dup2(proc->fd, STDIN_FILENO);
		close(proc->fd);
	}
	if (exec->rdr)
		redirect(exec->rdr, e, STDIN_FILENO, STDOUT_FILENO);
	if (proc->cmd)
	{
		if (proc->builtin)
			exit (do_builtin(proc->cmd, e, proc->builtin, STDOUT_FILENO));
		get_environment_for_exec(e);
		*proc->cmd = append_cmd_path(e, *proc->cmd);
		if (execve(*(proc->cmd), proc->cmd, e->env) == -1)
			ft_minishell_error("execve()", *proc->cmd, strerror(errno), errno);
	}
	else if (exec->subshell)
		executor(exec->subshell, e);
	exit (0);
}

int	fork_and_execute(t_exec *exec, t_env_info *e, t_process *proc)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		ft_minishell_error("fork()", NULL, strerror(errno), errno);
	else if (pid == 0)
		execute_child(exec, e, proc);
	if (proc->p)
	{
		proc->fd = dup(proc->p[0]);
		if (proc->fd == -1)
			ft_minishell_error("dup()", "duplicating read end of pipe for next command", strerror(errno), errno);
		if (close(proc->p[0]) == -1 || close(proc->p[1]) == -1)
			ft_minishell_error("close()", "closing pipe in main process", strerror(errno), errno);
	}
	return (pid);
}

void	init_proc(t_process *proc, int peepee)
{
	proc->cmd = NULL;
	proc->fd = 0;
	proc->builtin = 0;
	proc->is_first = 1;
	if (!peepee)
	{
		proc->p = malloc(2 * sizeof(int));
		if (!proc->p)
			ft_minishell_error("malloc()", "allocating pipe", strerror(errno), errno);
	}
	else
		proc->p = NULL;
}

int	exec_pipe_line(t_exec *exec, t_env_info *e)
{
	t_process	proc;
	pid_t		pid;
	int			status;

	init_proc(&proc, 0);
	while (exec)
	{
		if (prep_process(&proc, exec, e))
			return (free_dp(proc.cmd), e->last_exit_status);
		pid = fork_and_execute(exec, e, &proc);
		free_dp(proc.cmd);
		exec = exec->next;
	}
	if (proc.fd)
		close(proc.fd);
	waitpid(pid, &status, 0);
	while (wait(NULL) != -1)
		;
	if (WIFEXITED(e->last_exit_status))
		return (WEXITSTATUS(e->last_exit_status));
	else if (WIFSIGNALED(e->last_exit_status))
		return (128 + WTERMSIG(e->last_exit_status));
	return (EXIT_FAILURE);
}

void	executor(t_list *pipe_line, t_env_info *e)
{
	t_list	*to_free;

	while (pipe_line)
	{
		e->last_exit_status = exec_pipe_line(pipe_line->exec, e);
		to_free = pipe_line;
		if (!pipe_line->next)
			return (free_list(pipe_line));
		else if ((pipe_line->and_or == AND && !e->last_exit_status) || \
				(pipe_line->and_or == OR && e->last_exit_status))
		{
			pipe_line = pipe_line->next;
			to_free->next = NULL;
		}
		else
		{
			pipe_line = pipe_line->next->next;
			to_free->next->next = NULL;
		}
		free_list(to_free);
	}
}
