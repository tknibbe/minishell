/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 14:58:29 by tknibbe           #+#    #+#             */
/*   Updated: 2023/06/28 15:16:17 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	find_dollar(t_data *data, char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '$' && input[i] != SQUOT)
		i++;
	}
}

int	count_quote(char *input, t_data *data, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (input[i])
	{
		if (input[i] == c && data->token[i] == UNDEFINED)
			count++;
		i++;
	}
	return (count);
}
