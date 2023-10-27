#include <minishell.h>
#include <exec.h>

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
	else if (builtin_no == MS_CD)
		return (cd(cmd, e, out));
	else if (builtin_no == MS_PWD)
		return (pwd(out));
	ms_exit(cmd);
	return (1);
}

int	prep_process(t_process *proc, t_exec *exec, t_env_info *e)
{
	proc->cmd = full_expansion(exec->cmd, e);
	if (proc->cmd && *proc->cmd)
		proc->builtin = builtin(*proc->cmd);
	if (!exec->next)
	{
		free(proc->p);
		proc->p = NULL;
		if (proc->builtin && proc->is_first) // vraagtekens if else
		{
			if (exec->rdr && redirect(exec->rdr, e, -1, 3, proc->here_doc_nbr))
				e->last_exit_status =  do_builtin(proc->cmd, e, proc->builtin, 3);
			else
				e->last_exit_status =  do_builtin(proc->cmd, e, proc->builtin, 1);
			return (1);
		}
	}
	else if (pipe(proc->p) < 0)
		ft_minishell_error("pipe()", strerror(errno), NULL, errno);
	proc->is_first = 0;
	return (0);
}

