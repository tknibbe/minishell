#ifndef EXEC_H
# define EXEC_H

# include <parsing.h>
# include <minishell.h>

typedef struct s_exec		t_exec;
typedef struct s_str		t_str;
typedef struct s_minishell	t_ally;
typedef struct s_env_info	t_env_info;

typedef struct s_process
{
	int			fd;
	int			builtin;
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
// void	test_exec(char **env);
// void	execute_command(t_exec *t);
char	*append_cmd_path(t_env_info *env, char *cmd);

#endif