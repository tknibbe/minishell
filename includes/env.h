/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: cvan-sch <cvan-sch@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/29 16:01:53 by cvan-sch      #+#    #+#                 */
/*   Updated: 2023/07/06 17:03:39 by cvan-sch      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include <stdio.h>
# include <stdlib.h>

typedef struct s_env
{
	int		var_count;
	char	**env;
}			t_env;

t_env	*env_init(char *envp[]);
void	unset(t_env *env, char **to_unset);
void	export(t_env *env, char **to_export);
void	env(char **s);

void	env_dp(t_env *t, char *envp[]);
void	print_double_array(char **x);
void	reassign_export_items(char **env, char **to_export);
void	add_items(t_env *env, char **to_export);
char	*get_env(char *key, char **env);

#endif