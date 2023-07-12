/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: cvan-sch <cvan-sch@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/28 12:34:26 by cvan-sch      #+#    #+#                 */
/*   Updated: 2023/07/11 16:51:01 by cvan-sch      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <env.h>

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
	return (env);
}

void	unvalid_identifier(char **to_export, int i)
{
	write(2, "minishell: export: `", 21);
	write(2, to_export[i], ft_strlen(to_export[i]));
	write(2, "': not a valid identifier\n", 27);
	free(to_export[i]);
	move_pointers(NULL, 0, to_export, i);
}

void	validate_name(char **to_export)
{
	int	i;
	int	j;

	i = 0;
	while (to_export[i])
	{
		j = 0;
		while (to_export[i][j])
		{
			if (!ft_isalnum(to_export[i][j]) || to_export[i][j] == '_')
				break ;
			j++;
		}
		if (ft_isdigit(to_export[i][0]) ||\
			!ft_isalnum(to_export[i][j]) || to_export[i][j] == '_')
			unvalid_identifier(to_export, --i);
		i++;
	}
}

void	export(t_env *env, char **to_export)
{
	validate_name(to_export);
	reassign_export_items(env->env, to_export);
	add_items(env, to_export);
}

void	env(char **s)
{
	while (*s)
		printf("%s\n", *(s++));
}
