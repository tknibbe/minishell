/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 13:48:40 by tknibbe           #+#    #+#             */
/*   Updated: 2023/11/15 13:48:41 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "structs.h"

enum	e_builtin
{
	MS_NOBUILTIN,
	MS_ECHO,
	MS_CD,
	MS_PWD,
	MS_UNSET,
	MS_EXPORT,
	MS_ENV,
	MS_EXIT,
};

/*		executor.c*/
void	executor(t_list *pipe_line, t_env_info *e);

/*		executor_utils.c*/
int		do_builtin(char **cmd, t_env_info *e, int builtin_no, int out);
int		prep_process(t_process *proc, t_exec *exec, t_env_info *e);
int		builtin(char *cmd, int x);

/*		heredoc_expansion*/
void	do_heredoc_or_so(t_rdr *r, t_env_info *e, int hierdok_num, int in);

/*		redirect.c*/
int		redirect(t_rdr *r, t_env_info *e, int hierdok_num, int builtin);
char	*append_cmd_path(t_env_info *env, char *cmd);

#endif