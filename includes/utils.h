#ifndef UTILS_H
# define UTILS_H

#include "structs.h"

t_str	*tstr_new(char *content);
void	tstr_addback(t_str **head, t_str *new);
void	tstr_addnext(t_str *current, t_str *new);

int		ft_iswhitespace(int	c);
int		ft_isname(int c);
int		ft_isinset(int c, char *s);

char	*get_env(char *key, t_env_info *e);

void	print_double_array(char **x);
void	free_dp(char **dp);
int		count_dp(char **c);
int		ft_minishell_error(char *program, char *arg, char *desc, int ex);

#endif