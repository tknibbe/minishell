#include <minishell.h>
#include <expansion.h>
#include <built_ins.h>
#include <parsing.h>

t_list	*next_pipe_line(t_list *current)
{
	t_list	*ret;

	if (!current->next)
		return (free_list(current), NULL);
	// else if ((!current->exit_code && current->and_or == AND) ||\		TODO: !dit was de else if, exit code is verwijderd uit t_list dus jij (cris) moet even kijken of dit zo nog klopt <3
	// 		 (current->exit_code && current->and_or == OR))
	else if (current->and_or == AND || current->and_or == OR)
	{
		ret = current->next;
		current->next = NULL;
	}
	else
	{
		ret = current->next->next;
		current->next->next = NULL;
	}
	free_list(current);
	return (ret);
}

void	set_pipe(int *p)
{
	if (pipe(p) < 0)
		ft_minishell_error("pipe()", strerror(errno), NULL, errno);
}

int	builtin(char *cmd)
{
	if (!ft_strncmp("echo", cmd, 5))
		return (MS_ECHO);
	else if (!ft_strncmp("unset", cmd, 6))
		return (MS_UNSET);
	else if (!ft_strncmp("export", cmd, 7))
		return (MS_EXPORT);
	else if (!ft_strncmp("pwd", cmd, 4))
		return (MS_PWD);
	else if (!ft_strncmp("cd", cmd, 3))
		return (MS_CD);
	else if (!ft_strncmp("exit", cmd, 5))
		return (MS_EXIT);
	else if (!ft_strncmp("env", cmd, 4))
		return (MS_ENV);
	return (MS_NOBUILTIN);
}

int	do_builtin(char **cmd, t_env_info *e, int builtin_no, int out)
{
	if (builtin_no == MS_ECHO)
		return (echo(cmd, out));
	else if (builtin_no == MS_ENV)
		return (env(e->head, out));
	else if (builtin_no == MS_EXPORT)
		return (export(e, cmd));
	else if (builtin_no == MS_UNSET)
		return (unset(e, cmd));
	else if (builtin_no == MS_EXIT)
		return (ms_exit(cmd));
	else if (builtin_no == MS_CD)
		return (cd(cmd, e, out));
	else if (builtin_no == MS_PWD)
		return (pwd(cmd, out));
	return (-1);
}

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
		proc->builtin = builtin(*proc->cmd);
		if (proc->builtin)
			exit (do_builtin(proc->cmd, e, proc->builtin, STDOUT_FILENO));
		get_environment_for_exec(e);
		*proc->cmd = append_cmd_path(e, *proc->cmd);
		if (execve(*proc->cmd, proc->cmd, e->env) == -1)
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

	init_proc(&proc, 0);
	while (exec)
	{
		proc.cmd = full_expansion(exec->cmd, e);
		if (exec->next)
			set_pipe(proc.p);
		else
		{
			free(proc.p);
			proc.p = NULL;
		}
		pid = fork_and_execute(exec, e, &proc);
		exec = exec->next;
	}
	if (proc.fd)
		close(proc.fd);
	int status;
	waitpid(pid, &status, 0);
	while (wait(NULL) != -1)
		;
	if (WIFEXITED(e->last_exit_status))
		return (WEXITSTATUS(e->last_exit_status));
	else if (WIFSIGNALED(e->last_exit_status))
		return (128 + WTERMSIG(e->last_exit_status));
	return (EXIT_FAILURE);;
}

int	exec_single_cmd(t_exec *exec, t_env_info *e)
{
	int			b;
	char		**cmd;
	t_process	proc;

	cmd = full_expansion(exec->cmd, e); //TODO: cmd is leaking here. needs to be fixed pls/ //fixed on line 187. check if correct pls @crisss
	b = 0;
	if (cmd)
		b = builtin(*cmd);
	if (b)
	{
		if (exec->rdr && redirect(exec->rdr, e, -1, 3))
			return (do_builtin(cmd, e, b, 3));
		return (do_builtin(cmd, e, b, 1));
	}
	init_proc(&proc, 1);
	proc.cmd = cmd;
	waitpid(fork_and_execute(exec, e, &proc), &e->last_exit_status, 0);
	// if (proc.cmd)
	// 	free_dp(proc.cmd); //see above comment pls @criss
	if (WIFEXITED(e->last_exit_status))
		return (WEXITSTATUS(e->last_exit_status));
	else if (WIFSIGNALED(e->last_exit_status))
		return (128 + WTERMSIG(e->last_exit_status));
	return (EXIT_FAILURE);
}

void	executor(t_list *pipe_line, t_env_info *e)
{
	while (pipe_line)
	{
		// printf("executor %p\n", pipe_line->exec);
		if (!pipe_line->exec->next)
			e->last_exit_status = exec_single_cmd(pipe_line->exec, e);
		else
			e->last_exit_status = exec_pipe_line(pipe_line->exec, e);
		pipe_line = next_pipe_line(pipe_line);
	}
}
