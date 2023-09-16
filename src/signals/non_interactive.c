/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   non_interactive.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 13:41:26 by tknibbe           #+#    #+#             */
/*   Updated: 2023/09/15 12:59:20 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

//• In interactive mode:
//	ECHOCTL in termios (cl(set/get)attr) needs to be turned off
//	◦ ctrl-C displays a new prompt on a new line.
//	◦ ctrl-D exits the shell.
//	◦ ctrl-\ does nothing.

//non interactive mode:
//	ctrl-C exits whatever your running 
//	ctrl-\ is ignored
//	ctrl-D sends EOF -- is working automatically

void	non_inter_handler(int c)
{
	c = 0;
	ft_putchar_fd('\n', STDIN_FILENO);
}

void	set_echo(void)
{
	struct termios	term;

	if (!isatty(STDIN_FILENO))
	{
		//printf("script detected set_echo\n");
		return ;
	}
	if (tcgetattr(STDIN_FILENO, &term) != 0)
		ft_exit("Error getting terminal attributes", errno);
	term.c_lflag |= ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) != 0)
		ft_exit("Error setting terminal attributes", errno);
}

void	set_signals_non_inter(void)
{
	set_echo();
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, non_inter_handler);
}
