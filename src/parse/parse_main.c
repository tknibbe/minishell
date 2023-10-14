/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 14:21:38 by tknibbe           #+#    #+#             */
/*   Updated: 2023/10/06 14:48:42 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	split_pipe_and_parse(t_list **list, t_env_info *env)
{
	t_list	*temp;

	if (split_pipelines((*list)->input, list))
	{
		temp = *list;
		while (temp)
		{
			if (parse(temp->input, temp, env))
			{
				free_list((*list));
				return (EXIT_FAILURE);
			}
			temp = temp->next;
		}
	}
	else
	{
		if (parse((*list)->input, (*list), env))
		{
			free_list((*list));
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}
//TODO: fix only a quote as input

t_list	*parse_input(char *input, t_env_info *env)
{
	t_list	*list;

	if (!input[0])
	{
		env->last_exit_status = 1;
		return (NULL);
	}
	list = t_listnew();
	list->input = ft_strtrim(input, " "); // TODO: leaks if &&/|| in cmd
	tokenize(list);
	if (check_syntax(list, env))
	{
		// printf("returning NULL\n");
		return (NULL);
	}
	if (split_pipe_and_parse(&list, env))
		return (NULL);
	// printf("parser 2 %p\n", list->exec);
	// print_whole_list(list);
	return (list);
}
