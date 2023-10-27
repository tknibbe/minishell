#ifndef EXEC_H
# define EXEC_H

#include <stdbool.h>

typedef struct s_exec		t_exec;
typedef struct s_str		t_str;
typedef struct s_minishell	t_ally;
typedef struct s_env_info	t_env_info;
typedef struct s_env		t_env;

typedef struct s_process
{
	int			fd;
	int			builtin;
	bool		is_first;
	int			here_doc_nbr;
	int			*p;
	t_env_info	*e;
	char		**cmd;
}				t_process;

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

char	*append_cmd_path(t_env_info *env, char *cmd);
int		do_builtin(char **cmd, t_env_info *e, int builtin_no, int out);
int		builtin(char *cmd);
int		prep_process(t_process *proc, t_exec *exec, t_env_info *e);
void	execute_child(t_exec *exec, t_env_info *e, t_process *proc);
void	heredoc_write(t_str *str, t_env_info *e, int fd, int type);

#endif