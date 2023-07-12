/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 13:46:32 by tknibbe           #+#    #+#             */
/*   Updated: 2023/07/11 16:18:53 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	is_redirect(int c)
{
	if (c == PIPESYMBOL || c == REDIRRIGHT || c == REDIRLEFT \
		|| c == APPLEFT || c == APPRIGHT)
		return (1);
	return (0);
}

void	ft_syntax_error(char *str, char c)
{
	write(2, str, ft_strlen(str));
	if (c == '\n')
		write(2, "'newline'", 9);
	else
		write(2, &c, 1);
	write(2, "\n", 1);
}

int	check_syntax(t_data *data, char *input) // is wronk. can do < >
{
	int	previous;
	int	i;

	i = 0;
	previous = data->token[i];
	while (input[i])
	{
		while ((data->token[i] == previous || data->token[i] == BLANK) \
				&& input[i])
			i++;
		if (is_redirect(previous) && is_redirect(data->token[i]))
		{
			ft_syntax_error("Minishell: syntax error near unexpected token ", \
				input[i]);
			return (1);
		}
		previous = data->token[i];
	}
	return (0);
}
