/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 14:21:38 by tknibbe           #+#    #+#             */
/*   Updated: 2023/10/18 16:01:15 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*Description:
split_pipe_and_parse is a function responsible for splitting input into separate pipelines, each of which is then parsed into individual commands.
It facilitates the execution of multiple commands separated by pipe symbols.

Parameters:

    list (t_list**): A pointer to a pointer to a t_list structure representing the input and parsed data.
    env (t_env_info*): Environment information.

Return Value:

    EXIT_SUCCESS on successful splitting and parsing.
    EXIT_FAILURE if any errors occur during this process.*/
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

/*Description:
parse_input is a function designed to parse user input and generate a structured t_list representing the parsed input.
It handles input validation, memory management, tokenization, syntax checking, and parsing of command segments separated by pipes.

Parameters:

    input (char*): The user's input string to be parsed.
    env (t_env_info*): Environment information.

Return Value:

    A pointer to a t_list structure containing the parsed input or NULL in case of errors.*/
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
	if (!list->input)
		ft_minishell_error("ft_strtrim()", "failed", strerror(errno), errno);
	tokenize(list);
	if (check_syntax(list, env))
		return (free_list(list), NULL);
	if (split_pipe_and_parse(&list, env))
		return (NULL);
	return (list);
}
