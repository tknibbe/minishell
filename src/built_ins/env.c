/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: cvan-sch <cvan-sch@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/28 12:34:26 by cvan-sch      #+#    #+#                 */
/*   Updated: 2023/06/28 17:02:07 by cvan-sch      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	count(char **c)
{
	int	i;

	i = 0;
	while (c[i])
		i++;
	return (i);
}

char **free_dp(char **dp)
{
	int	i;

	i = 0;
	while (dp[i])
	{
		free(dp[i]);
		i++;
	}
	free(dp);
	return (NULL);
}

void	env_dp(t_env *t, char *envp[])
{
	int		i;
	char	**env;

	env = malloc((count(envp) + 1) * sizeof(char *));
	if (!env)
		return ;
	i = 0;
	while (envp[i])
	{
		env[i] = ft_strdup(envp[i]);
		if (!env[i])
		{
			free_dp(env);
			return ;
		}
		i++;
	}
	env[i] = NULL;
	t->var_count = i;
	t->env = env;
}

t_env	*env_init(char *envp[])
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	env_dp(env, envp);
	// int i = 0;
	// while (env->env[i])
	// {
	// 	printf("%s\n", env->env[i]);
	// 	i++;
	// }
	return (env);
}

// int	check_what_to_export(char **old_env, char **to_export)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (to_export[i])
// 	{
// 		j = 0;
// 		while (old_env[j])
// 		{
			
// 		}
// 	}
// 	return 0;
// }

// void	export(t_env *env, char **to_export)
// {
// 	char	**new_env;
// 	int		i;

// }
