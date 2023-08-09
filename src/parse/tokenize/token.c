/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 12:18:15 by tknibbe           #+#    #+#             */
/*   Updated: 2023/08/09 11:44:53 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <parsing.h>

static void	set_token(t_list *list, char *input);

/*sets tokens according to the ENUMs defined in the header. 
returns 0 on succes.*/
int	tokenize(char *input, t_list *list)
{
	int	len;

	len = ft_strlen(input);
	list->token = malloc(sizeof(int) * len);
	if (!list->token)
		ft_exit("Malloc error\n", errno);
	set_token(list, input);
	//print_tokens(*list, input);
	return (0);
}

int	is_rdr_pipe_amp(char c)
{
	if (c == '|' || c == '<' || c == '>' || c == '&')
		return (1);
	return (0);
}

static int	is_closed_quote(char *input, int *end_quote, int i)
{
	char	quote;

	if (input[i] != '"' && input[i] != '\'')
		return (0);
	*end_quote = i + 1;
	quote = input[i];
	i++;
	while (input[i])
	{
		*end_quote += 1;
		if (input[i] == quote)
			return (1);
		i++;
	}
	*end_quote = 0;
	return (0);
}

static void	set_token(t_list *list, char *input)
{
	int	i;
	int	end_quote;

	i = 0;
	end_quote = 0;
	while (input[i])
	{
		if (is_closed_quote(input, &end_quote, i))
		{
			while (i < end_quote)
			{
				list->token[i] = WORD;
				i++;
			}
		}
		if (is_rdr_pipe_amp(input[i]))
		{
			set_rdr_pipe_amp(list, input, &i);
			i++;
		}
		else
		{
			if (!ft_whitespace(input[i]))
				list->token[i] = WORD;
			else
				list->token[i] = BLANK;
			i++;
		}
	}
}
