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
# include <termios.h>

# define PROMPT "ez_game -> "

//hey crissie baby <3
//hey tymoo daddy 8=D
//hey crissie deel 2 80085
//hey tymoo bicep baby muscle mommy

typedef struct s_list	t_list;

typedef struct	s_str
{
	char			*str;
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

t_str	*tstr_new(char *content);
void	tstr_addback(t_str **head, t_str *new);
void	tstr_addnext(t_str *current, t_str *new);

t_env_info	*env_init(char **env);

//expansion
char	**full_expansion(t_str *c, t_env_info *e);

//SIGNALS
void	set_signals_inter(void);
void	unset_echo(void);
void	set_signals_non_inter(void);
void	set_echo(void);

int	ft_minishell_error(char *program, char *arg, char *desc, int ex);

#endif
