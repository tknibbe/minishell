/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 14:21:38 by tknibbe           #+#    #+#             */
/*   Updated: 2023/10/05 14:25:23 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	split_pipe_and_parse(t_list *list, t_env_info *env)
{
	t_list	*temp;

	if (split_pipelines(list->input, &list))
	{
		temp = list;
		while (temp)
		{
			if (parse(temp->input, temp, env))
			{
				free_list(list);
				return (NULL);
			}
			temp = temp->next;
		}
	}
	else
	{
		if (parse(list->input, list, env))
		{
			free_list(list);
			return (NULL);
		}
	}
}

t_list	*parse_input(char *input, t_env_info *env)
{
	t_list	*list;

	if (!input[0])
	{
		env->last_exit_status = 1;
		return (NULL);
	}
	list = t_listnew();
	list->input = ft_strtrim(input, " ");
	tokenize(list);
	if (check_syntax(list, env))
		return (NULL);
	if (split_pipe_and_parse(list, env))
		return (NULL);
	return (list);
}
