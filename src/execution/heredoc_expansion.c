/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expansion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tymonknibbe <tymonknibbe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 16:13:53 by tymonknibbe       #+#    #+#             */
/*   Updated: 2023/10/27 17:16:39 by tymonknibbe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exec.h>
#include <minishell.h>
#include <built_ins.h>

static void	write_expand(char *str, t_env_info *e, int fd)
{
	int		i;
	int		start;
	char	*temp;

	i = 0;
	start = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			write(fd, &str[start], i++ - start);
			temp = get_env(&str[i], e);
			while (ft_isname(str[i]))
				i++;
			// printf("temp = [%s] i = %d\n", temp, i);
			start = i;
			if (temp)
				write(fd, temp, ft_strlen(temp));
			free(temp);
		}
		i++;
	}
	// printf("start = %d\n", start);
	write(fd, &str[start], i - start);
}

void	heredoc_write(t_str *str, t_env_info *e, int fd, int type)
{
	while (str)
	{
		if (type == HEREDOC_NO_EXP)
			write(fd, str->str, ft_strlen(str->str));
		else
			write_expand(str->str, e, fd);
		str = str->next;
	}
}