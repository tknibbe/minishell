/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   split_args.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tknibbe <tknibbe@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/08 16:59:19 by tknibbe       #+#    #+#                 */
/*   Updated: 2023/07/20 14:54:28 by cvan-sch      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int		get_num_args(char *input, t_list *list);
char	*split_on_token(t_list *list, char *input, int *start);

char	**split_args(char *input, t_list *list)
{
	int		i;
	char	**args;
	int		num_args;
	int		j;

	i = 0;
	j = 0;
	num_args = get_num_args(input, list);
	args = malloc(sizeof(char *) * num_args + 1);
	while (i < num_args)
	{
		args[i] = split_on_token(list, input, &j);
		i++;
	}
	args[i] = NULL;
	return (args);
}

int	more_to_parse(int i, char *input, t_list *list)
{
	while (input[i])
	{
		if (list->token[i] != BLANK)
			return (1);
		i++;
	}
	return (0);
}

int	get_num_args(char *input, t_list *list)
{
	int	i;
	int	num;
	int	token;

	i = 0;
	num = 0;
	while (input[i] && more_to_parse(i, input, list))
	{
		while (input[i] == SPACE)
			i++;
		num++;
		token = list->token[i];
		while (list->token[i] == token && input[i])
		{
			i++;
		}
	}
	//printf("get_num_args %d\n", num);
	return (num);
}

char	*split_on_token(t_list *list, char *input, int *start)
{
	int		i;
	int		token;
	char	*str;
	int		j;

	token = list->token[*start];
	i = *start;
	j = 0;
	while (list->token[i] == token && input[i])
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
	while (list->token[*start] == BLANK && input[*start])
		*start += 1;
	return (str);
}
