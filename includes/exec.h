#ifndef EXEC_H
# define EXEC_H

# include <parsing.h>
# include <minishell.h>

typedef struct s_exec		t_exec;
typedef struct s_str		t_str;
typedef struct s_minishell	t_ally;
typedef struct s_env_info	t_env_info;


void	test_exec(char **env);
void	execute_command(t_exec *t);
char	*append_cmd_path(t_env_info *env, char *cmd);
#endif