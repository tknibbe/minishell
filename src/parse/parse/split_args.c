/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 16:59:19 by tknibbe           #+#    #+#             */
/*   Updated: 2023/07/08 18:37:48 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int		get_num_args(char *input, t_data *data);
char	*split_on_token(t_data *data, char *input, int *start);

char	**split_args(char *input, t_data *data)
{
	int		i;
	char	**args;
	int		num_args;
	int		j;

	i = 0;
	j = 0;
	num_args = get_num_args(input, data);
	args = malloc(sizeof(char *) * num_args + 1);
	while (i < num_args)
	{
		args[i] = split_on_token(data, input, &j);
		i++;
	}
	args[i] = NULL;
	return (args);
}

int	more_to_parse(int i, char *input, t_data *data)
{
	while (input[i])
	{
		if (data->token[i] != BLANK)
			return (1);
		i++;
	}
	return (0);
}

int	get_num_args(char *input, t_data *data)
{
	int	i;
	int	num;
	int	token;

	i = 0;
	num = 0;
	while (input[i] && more_to_parse(i, input, data))
	{
		while (input[i] == SPACE)
			i++;
		num++;
		token = data->token[i];
		while (data->token[i] == token && input[i])
		{
			i++;
		}
	}
	//printf("get_num_args %d\n", num);
	return (num);
}

char	*split_on_token(t_data *data, char *input, int *start)
{
	int		i;
	int		token;
	char	*str;
	int		j;

	token = data->token[*start];
	i = *start;
	j = 0;
	while (data->token[i] == token && input[i])
		i++;
	str = malloc(sizeof(char) * (i - *start + 1)); //prtoct
	if (!str)
		ft_exit("Malloc error\n", errno);
	while (*start < i)
	{
		str[j] = input[*start];
		*start += 1;
		j++;
	}
	str[j] = '\0';
	while (data->token[*start] == BLANK && input[*start])
		*start += 1;
	return (str);
}
