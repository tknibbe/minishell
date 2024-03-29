/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_pwd_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 12:33:05 by tknibbe           #+#    #+#             */
/*   Updated: 2023/11/22 15:51:50 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_flag(char *flag, int *new_line)
{
	int	i;

	if (!ft_strncmp(flag, "-n", 2))
	{
		i = 2;
		while (flag[i] && flag[i] == 'n')
			i++;
		if (!flag[i])
		{
			*new_line = 0;
			return (2);
		}
	}
	*new_line = 1;
	return (1);
}

/*
	echo function will write it's arguments to the standard output
	seperated by a space.
	if -n option is supplied at the start of it's argument, newline will be skipped
	otherwise it will end sentence with a newline
*/
int	echo(char **cmd, int fd)
{
	int		i;
	int		new_line;

	i = check_flag(cmd[1], &new_line);
	while (cmd[i])
	{
		write(fd, cmd[i], ft_strlen(cmd[i]));
		if (cmd[++i])
			write(fd, " ", 1);
	}
	if (new_line)
		write(fd, "\n", 1);
	if (fd != 1)
		close(fd);
	return (0);
}

void	ms_exit(char **cmd, t_env_info *e)
{
	int	i;

	if (*(cmd + 1) && *(cmd + 2))
		ft_minishell_error("exit", NULL, \
			"too many arguments", 1);
	if (!cmd[1])
		exit(e->last_exit_status);
	i = 0;
	if (cmd[1][i] == '-' || cmd[1][i] == '+')
		i++;
	while (cmd[1][i] >= '0' && cmd[1][i] <= '9')
		i++;
	if (cmd[1][i])
		ft_minishell_error("exit()", cmd[1], "numeric argument required", 2);
	exit(ft_atoi(cmd[1]));
}

/*
	will print the current working directory
	followed by a new line
*/
int	pwd(int fd)
{
	char	*buff;

	buff = getcwd(NULL, 0);
	if (!buff)
		return (ft_minishell_error("getcwd()", strerror(errno), NULL, 0));
	write(fd, buff, ft_strlen(buff));
	write(fd, "\n", 1);
	free(buff);
	if (fd != 1)
		close(fd);
	return (0);
}
