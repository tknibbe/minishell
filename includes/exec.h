#ifndef EXEC_H
# define EXEC_H

# include <parsing.h>

typedef struct s_exec		t_exec;
void	test_exec(char **env);
void	execute_command(t_exec *t);

#endif