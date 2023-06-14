/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_and_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 16:07:59 by tknibbe           #+#    #+#             */
/*   Updated: 2023/06/14 16:49:57 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//bash will read only one line at a time unless the very last char is '\' is there is a char after '\' it wont read next line

char	**parse_input(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		while (input[i] != '\n' && input[i])
		{
			if (input[i] == '\n' && input[i - 1] == 92) //if the last char is a '\' (92) it'll continue reading
				i++;
			write(1, &input[i], 1);
			write(1, " ", 1);
			i++;
		}
		i++;
	}
	return (NULL);
}

char	**parse_and_execute(char *input)
{
	char **result;
	result = parse_input(input);
	//do_history_ofzo();
	//execute();
	return (NULL);
}
