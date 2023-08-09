#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <sys/wait.h>
# include <sys/errno.h>
# include <fcntl.h>
# include <string.h>
# include "../lib/includes/libft.h"
# include <parsing.h>
# include <exec.h>
# include <built_ins.h>
# include <signal.h>
# include <sys/ioctl.h>

//hey crissie baby <3
//hey tymoo daddy 8=D
//hey crissie deel 2 80085

typedef struct s_list	t_list;

typedef struct s_str
{
	char			*s;
	struct s_str	*next;
}					t_str;

typedef struct s_minishell
{
	t_env_info			*env;
	t_list				*list;
	int					exit_code;
}						t_ally;

void	history(const char *s);
//void	parse_input(char *input, t_ally *all);

//EXIT_FUNCS.C
void	ft_exit(char *string, int errnum);

//utils
void	print_double_array(char **x);
void	free_dp(char **dp);
int		count(char **c);

int		ft_iswhitespace(int	c);
int		ft_isname(int c);
int		ft_isinset(int c, char *s);

t_env_info	*env_init(char **env);

//expansion
void		test_env_expansion_shit(t_ally *all, char *input);

//SIGNALS
void	set_signals_inter(void);
void	set_signals_non_inter(void);

#endif
