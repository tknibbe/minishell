/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: cvan-sch <cvan-sch@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/29 16:01:53 by cvan-sch      #+#    #+#                 */
/*   Updated: 2023/07/13 15:44:35 by cvan-sch      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include <stdio.h>
# include <stdlib.h>


typedef struct s_env
{
	char			*key;
	char			*value;
	char			*joined_value;
	struct s_env	*next;
}					t_env;

typedef struct s_env_info
{
	int		count;
	int		has_changed;
	char	**env;
	t_env	*head;
}			t_env_info;

t_env_info		*env_init(char **env);
t_env			*env_new(char *s);
void			env_addback(t_env **head, t_env *new);

void			env(t_env *env);
void			unset(t_env_info *e, char **to_unset);
void			export(t_env_info *e, t_env *env, char **to_export);

void			add_the_rest(t_env_info *e, t_env *env, char **to_export);
void			move_pointer(char **s, int i);
unsigned int	check_valid_name(char *s);
char			*ft_envjoin(char *s1, char *s2);
void			create_env_for_execution(t_env_info *e);

// t_env	*env_init(char *envp[]);
// void	unset(t_env *env, char **to_unset);
// void	export(t_env *env, char **to_export);
// void	env(char **s);

// void	env_dp(t_env *t, char *envp[]);
// void	print_double_array(char **x);
// void	reassign_export_items(char **env, char **to_export);
// void	add_items(t_env *env, char **to_export);
// char	*get_env(char *key, char **env);

// void	move_pointers(char **env, int i, char **to_export, int j);

#endif