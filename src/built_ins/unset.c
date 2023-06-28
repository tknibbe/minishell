/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: cvan-sch <cvan-sch@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/28 16:08:40 by cvan-sch      #+#    #+#                 */
/*   Updated: 2023/06/28 17:55:46 by cvan-sch      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	print_double_array(char **x)
{
	while (*x)
	{
		printf("%s\n", *x);
		x++;
	}
	
}

int	to_remove(char **env, char **to_unset)
{
	int	i;
	int	j;
	int	k;
	int	to_remove;

	i = 0;
	to_remove = 0;
	while (to_unset[i])
	{
		j = 0;
		while (env[j])
		{
			k = 0;
			while (env[j][k] == to_unset[i][k])
				k++;
			if (env[j][k] == '=' && to_unset[i][k] == '\0')
			{
				to_remove++;
				break ;
			}
			j++;
		}
		i++;
	}
	return (to_remove);
}

void	reassign_pointers(char **src, char **dst, char **to_unset)
{
	int	x;
	int	y;
	int	z;

	x = 0;
	z = 0;
	while (src[x])
	{
		y = 0;
		while (to_unset[y])
		{
			if (!ft_strncmp(src[x], to_unset[y], ft_strlen(to_unset[y])))
				break ;
			y++;
		}
		if (!to_unset[y])
			dst[z++] = src[x];
		x++;
	}
	dst[z] = NULL;
}

void	unset(t_env *env, char **to_unset)
{
	int	i;
	char **new_env;

	i = to_remove(env->env, to_unset);
	printf("i: %d\nvar_count: %d\n", i, env->var_count);
	if (!i)
		return ; // I could free to_unset here
	new_env = malloc((env->var_count - i + 1) * sizeof(char *));
	if (!new_env)
		ft_exit("allocation error\n", 1);
	reassign_pointers(env->env, new_env, to_unset);
	free(env->env);
	env->env = new_env;
	env->var_count -= i;
	i = 0;
	printf("\n %d ================\n", env->var_count);
	while (env->env[i])
	{
		printf("%d, %s\n", i + 1, env->env[i]);
		i++;
	}
}