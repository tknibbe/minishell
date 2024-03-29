/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 12:32:47 by tknibbe           #+#    #+#             */
/*   Updated: 2023/11/15 12:32:48 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	will print out all keys with their value's
*/
int	env(t_env *env, int fd)
{
	while (env)
	{
		write(fd, env->joined_value, ft_strlen(env->joined_value));
		write(fd, "\n", 1);
		env = env->next;
	}
	return (0);
}

static void	only_export(char *arg, t_env *head, int fd)
{
	if (arg)
		return ;
	while (head)
	{
		write(fd, head->key, ft_strlen(head->key));
		write(fd, "=\"", 2);
		write(fd, head->value, ft_strlen(head->value));
		write(fd, "\"\n", 2);
		head = head->next;
	}
}

/*will create or adjust an environment variable for export*/
int	export(t_env_info *e, char **to_export, int fd)
{
	int		i;
	int		mode;
	int		ret;

	i = 1;
	ret = 0;
	only_export(to_export[1], e->head, fd);
	while (to_export[i])
	{
		mode = legit_export_item(to_export[i]);
		if (mode < 1)
		{
			if (!find_and_export(e, e->head, to_export[i]))
			{
				env_addback(&e->head, env_new(to_export[i]));
				e->count++;
			}
			e->has_changed = 1;
		}
		else if (mode > 1)
			ret = ft_minishell_error("export", to_export[i], \
			"not a valid identifier", 0);
		i++;
	}
	return (ret);
}

/*will unset/remove a variable from environment given the key*/
int	unset(t_env_info *e, char **unset)
{
	int	i;
	int	ret;

	i = 1;
	ret = 0;
	while (unset[i])
	{
		if (valid_identifier(unset[i]))
		{
			if (find_and_unset(&e->head, unset[i]))
			{
				e->has_changed = 1;
				e->count--;
			}
		}
		else
			ret = ft_minishell_error("export", unset[i], \
			"not a valid identifier", 0);
		i++;
	}
	return (ret);
}
