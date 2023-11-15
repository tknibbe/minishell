/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 12:34:14 by tknibbe           #+#    #+#             */
/*   Updated: 2023/11/15 12:34:15 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	int	ret;

	ret = 0;
	if (builtin_no == MS_ECHO)
		ret = echo(cmd, out);
	else if (builtin_no == MS_ENV)
		ret = env(e->head, out);
	else if (builtin_no == MS_EXPORT)
		ret = export(e, cmd, out);
	else if (builtin_no == MS_UNSET)
		ret = unset(e, cmd);
	else if (builtin_no == MS_CD)
		ret = cd(cmd, e, out);
	else if (builtin_no == MS_PWD)
		ret = pwd(out);
	else
		ms_exit(cmd);
	if (out == 3)
		close(out);
	return (ret);
}

int	prep_process(t_process *proc, t_exec *exec, t_env_info *e)
{
	int	fd;

	proc->cmd = full_expansion(exec->cmd, e);
	if (proc->cmd && *proc->cmd)
		proc->builtin = builtin(*proc->cmd);
	if (proc->is_single_command && proc->builtin)
	{
		fd = redirect(exec->rdr, e, 1, 1);
		if (fd > 0)
			e->last_exit_status = do_builtin(proc->cmd, e, proc->builtin, fd);
		if (fd == 3)
			close(fd);
		return (1);
	}
	else if (!proc->is_single_command && !exec->next)
	{
		free(proc->p);
		proc->p = NULL;
	}
	else if (exec->next && pipe(proc->p) < 0)
		ft_minishell_error("pipe()", strerror(errno), NULL, errno);
	return (0);
}
