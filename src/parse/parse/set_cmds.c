/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cmds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tymonknibbe <tymonknibbe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 14:13:45 by tknibbe           #+#    #+#             */
/*   Updated: 2023/07/12 21:50:29 by tymonknibbe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**get_cmd(t_data *data, char *input, int *j);
char	*get_substr(t_data *data, char *input, int *j);
int		count_cmds(t_data *data, char *input, int *j);

void	set_cmds(t_data **data, char *input, int node_amount)
{
	int		i;
	int		j;
	t_exec	*node;

	i = 0;
	j = 0;
	node = (*data)->list;
	while (i < node_amount)
	{
		node->cmd = get_cmd(*data, input, &j);
		node = node->next;
		i++;
	}
}

char	**get_cmd(t_data *data, char *input, int *j)
{
	int		len;
	int		i;
	char	**ret_str;

	i = 0;
	len = count_cmds(data, input, j);
	ret_str = malloc(sizeof(char *) * len + 1);
	if (!ret_str)
		ft_exit("Malloc error\n", errno);
	while (i < len)
	{
		ret_str[i] = get_substr(data, input, j);
		ret_str[i] = trim_quotes(ret_str[i]);
		i++;
	}
	ret_str[len] = NULL;
	return (ret_str);
}

char	*get_substr(t_data *data, char *input, int *j)
{
	int		i;
	int		start;
	char	*str;
	int		len;

	len = 0;
	while ((data->token[*j] == PIPESYMBOL || data->token[*j] == BLANK) \
			&& input[i])
		*j += 1;
	start = *j;
	while (data->token[*j] != PIPESYMBOL && data->token[*j] != BLANK \
			&& input[*j])
	{
		*j += 1;
		len++;
	}
	str = ft_substr(input, start, len);
	return (str);
}

int	count_cmds(t_data *data, char *input, int *j)
{
	int	len;
	int	i;

	i = *j;
	len = 0;
	while ((data->token[i] == PIPESYMBOL || data->token[i] == BLANK) \
			&& input[i])
		i++;;
	//printf("countentry point [%c][%d]\n", input[*j], *j);
	while (input[i] && data->token[i] != PIPESYMBOL)
	{
		if (input[i + 1] && data->token[i] != BLANK \
			&& data->token[i + 1] == BLANK && data->token[i + 1] != PIPESYMBOL)
			{
				len++;
			}
		else if (data->token[i] != BLANK && !input[i + 1])
			len++;
		i++;
	}
	//*j = i;
	return (len);
}

char *trim_quotes(char *str)
{
	char	quote[2];

	quote[0] = 34;
	quote[1] = '\0';
	if (!ft_strncmp(str, "'", 1))
		return (ft_strtrim(str, "'"));
	if (!ft_strncmp(str, quote, 1))
		return (ft_strtrim(str, quote));
	return (str);
}
