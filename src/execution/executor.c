/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 12:34:10 by tknibbe           #+#    #+#             */
/*   Updated: 2023/11/19 14:09:25 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execute_child(t_exec *exec, t_env_info *e, t_process *proc)
{
	if (proc->p)
	{
		close(proc->p[0]);
		dup2(proc->p[1], STDOUT_FILENO);
		close(proc->p[1]);
	}
	if (proc->fd_to_read_from)
	{
		dup2(proc->fd_to_read_from, STDIN_FILENO);
		close(proc->fd_to_read_from);
	}
	if (exec->rdr)
		redirect(exec->rdr, e, proc->here_doc_nbr, 0);
	if (proc->cmd && *proc->cmd)
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
	exit (e->last_exit_status);
}

static int	fork_and_execute(t_exec *exec, t_env_info *e, t_process *proc)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		ft_minishell_error("fork()", NULL, strerror(errno), errno);
	else if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		execute_child(exec, e, proc);
	}
	if (proc->fd_to_read_from)
		close(proc->fd_to_read_from);
	if (proc->p)
	{
		proc->here_doc_nbr++;
		proc->fd_to_read_from = dup(proc->p[0]);
		if (proc->fd_to_read_from == -1)
			ft_minishell_error("dup()", "duplicating read end of \
				pipe for next command", strerror(errno), errno);
		if (close(proc->p[0]) == -1 || close(proc->p[1]) == -1)
			ft_minishell_error("close()", "closing pipe in main process", \
				strerror(errno), errno);
	}
	return (pid);
}

static void	init_proc(t_process *proc, t_exec *next)
{
	proc->cmd = NULL;
	proc->fd_to_read_from = 0;
	proc->builtin = 0;
	proc->here_doc_nbr = 1;
	if (!next)
	{
		proc->is_single_command = 1;
		proc->p = NULL;
		return ;
	}
	proc->is_single_command = 0;
	proc->p = malloc(2 * sizeof(int));
	if (!proc->p)
		ft_minishell_error("malloc()", "allocating pipe", \
			strerror(errno), errno);
}

static int	exec_pipe_line(t_exec *exec, t_env_info *e)
{
	t_process	proc;
	pid_t		pid;
	int			status;

	init_proc(&proc, exec->next);
	while (exec)
	{
		if (prep_process(&proc, exec, e))
			return (free_dp(proc.cmd), e->last_exit_status);
		pid = fork_and_execute(exec, e, &proc);
		free_dp(proc.cmd);
		exec = exec->next;
	}
	if (proc.fd_to_read_from)
		close(proc.fd_to_read_from);
	waitpid(pid, &status, 0);
	while (wait(NULL) != -1)
		;
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (EXIT_FAILURE);
}

void	executor(t_list *pipe_line, t_env_info *e)
{
	t_list	*to_free;
	t_list	*temp;

	while (pipe_line)
	{
		e->last_exit_status = exec_pipe_line(pipe_line->exec, e);
		if (!pipe_line->next)
			return (free_list(pipe_line));
		to_free = pipe_line;
		while (pipe_line)
		{
			if ((e->last_exit_status && pipe_line->and_or == OR) || \
				(!e->last_exit_status && pipe_line->and_or == AND))
			{
				temp = pipe_line;
				pipe_line = pipe_line->next;
				temp->next = NULL;
				break ;
			}
			pipe_line = pipe_line->next;
		}
		free_list(to_free);
	}
}
