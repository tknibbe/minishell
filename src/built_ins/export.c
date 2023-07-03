/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: cvan-sch <cvan-sch@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/29 16:32:24 by cvan-sch      #+#    #+#                 */
/*   Updated: 2023/07/02 12:52:05 by cvan-sch      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <env.h>
#include <minishell.h>

static int	to_compare(char *s, int *pe)
{
	int	i;
	int	j;

	i = 0;
	while (s[i] && s[i] != '=')
		i++;
	if (i && s[i] == '=' && s[i - 1] == '+')
	{
		j = i;
		while (s[i])
		{
			s[i - 1] = s[i];
			i++;
		}
		s[i - 1] = '\0';
		*pe = 1;
		return (j);
	}
	if (!s[i])
		return (i);
	return (i + 1);
}

static void	move_pointers(char **env, int i, char **to_export, int j)
{
	free(env[i]);
	env[i] = to_export[j];
	if (!to_export[j])
		return ;
	while (to_export[j + 1])
	{
		to_export[j] = to_export[j + 1];
		j++;
	}
	to_export[j] = NULL;
}

static void	join_values(char **env, int i, char **to_export, int j)
{
	int		k;
	int		l;
	char	*tmp;

	k = 0;
	while (to_export[j][k] && to_export[j][k] != '=')
		k++;
	tmp = ft_strjoin(env[i], &to_export[j][k + 1]);
	free(to_export[j]);
	to_export[j] = tmp;
}

void	release_pointer(char **x, int i)
{
	free(x[i]);
	while (x[i + 1])
	{
		x[i] = x[i + 1];
		i++;
	}
	x[i] = NULL;
}

void	reassign_export_items(char **env, char **to_export)
{
	int		i;
	int		j;
	int		cmp;
	int		plus_equals;

	i = 0;
	while (to_export[i])
	{
		if (!ft_strchr(to_export[i], '='))
		{
			release_pointer(to_export, i);
			continue ;
		}
		j = 0;
		plus_equals = 0;
		cmp = to_compare(to_export[i], &plus_equals);
		while (env[j])
		{
			if (!ft_strncmp(env[j], to_export[i], cmp))
			{
				if (plus_equals)
					join_values(env, j, to_export, i);
				move_pointers(env, j, to_export, i--);
				break ;
			}
			j++;
		}
		i++;
	}
}

void	add_items(t_env *env, char **to_export)
{
	char	**new_env;
	int		i;
	int		j;

	new_env = malloc((env->var_count + count(to_export) + 1) * sizeof(char *));
	if (!new_env)
		ft_exit("Error: allocation failed\n", errno);
	i = 0;
	while (env->env[i])
	{
		new_env[i] = env->env[i];
		i++;
	}
	j = 0;
	while (to_export[j])
	{
		new_env[i] = to_export[j];
		i++;
		j++;
	}
	new_env[i] = NULL;
	free(to_export);
	free(env->env);
	env->env = new_env;
}
