#ifndef UTILS_H
# define UTILS_H

# include "structs.h"
# include "minishell.h"

/*		t_str utils*/
t_str	*tstr_new(char *content);
void	tstr_addback(t_str **head, t_str *new);
void	tstr_addnext(t_str *current, t_str *new);

/*		is something utils*/
int		ft_iswhitespace(int	c);
int		ft_isname(int c);
int		ft_isinset(int c, char *s);

/*		get environment variable*/
char	*get_env(char *key, t_env_info *e);

/*		double pointer utils*/
void	print_double_array(char **x);
void	free_dp(char **dp);
int		count_dp(char **c);
void	free_list(t_list *lst);
int		ft_minishell_error(char *program, char *arg, char *desc, int ex);

/*		signals*/
void	unset_echo(void);
void	set_signals_inter(void);
void	set_signals_non_inter(void);

#endif