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

t_list	*next_pipe_line(t_list *current)
{
	t_list	*ret;

	//printf("free current node");
	if (!current->next)
		return (free_list(current), NULL);
	else if ((!current->exit_code && current->and_or == AND) ||\
			 (current->exit_code && current->and_or == OR))
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

int	builtin(char **cmd, t_env_info *e)
{
	if (!ft_strncmp("echo", *cmd, 5))
		echo(cmd);
	else if (!ft_strncmp("unset", *cmd, 6))
		unset(e, cmd);
	else if (!ft_strncmp("export", *cmd, 7))
		export(e, cmd);
	else if (!ft_strncmp("pwd", *cmd, 4))
		pwd(cmd);
	else if (!ft_strncmp("cd", *cmd, 3))
		cd(cmd, e);
	else if (!ft_strncmp("exit", *cmd, 5))
		exit(0);
	else if (!ft_strncmp("env", *cmd, 4))
		env(e->head);
	else
		return (0);
	return (1);
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
		redirect(exec->rdr, e);
	if (proc->cmd && !builtin(proc->cmd, e))
	{
		get_environment_for_exec(e);
		*proc->cmd = append_cmd_path(e, *proc->cmd);
		if (execve(*proc->cmd, proc->cmd, e->env) == -1)
			ft_minishell_error("execve()", *proc->cmd, strerror(errno), errno);
	}
	else if (exec->subshell)
	{
		printf("subshell needs to be executed\n");
		exit(0);
	}
}

int	fork_and_execute(t_exec *exec, t_env_info *e, t_process *proc)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		ft_minishell_error("fork()", strerror(errno), NULL, errno);
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

void	init_proc(t_process *proc)
{
	proc->cmd = NULL;
	proc->fd = 0;
	proc->p = malloc(2 * sizeof(int));
	if (!proc->p)
		ft_minishell_error("malloc()", "allocating pipe", strerror(errno), errno);
}

int	exec_pipe_line(t_exec *exec, t_env_info *e)
{
	t_process	proc;
	pid_t		pid;

	init_proc(&proc);
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
	return (WEXITSTATUS(status));
}

void	executor(t_list *pipe_line, t_env_info *e)
{
	while (pipe_line)
	{
		pipe_line->exit_code = exec_pipe_line(pipe_line->exec, e);
		//printf("exit code: %d\n", pipe_line->exit_code);
		pipe_line = next_pipe_line(pipe_line);
	}
}
