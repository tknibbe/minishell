/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 13:41:26 by tknibbe           #+#    #+#             */
/*   Updated: 2023/08/08 15:33:11 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <termios.h>


void	interactive_handler(int c)
{
	ft_putchar_fd('\n', STDIN_FILENO);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	non_inter_handler(int c)
{
	//printf("interuppted\n");
	//global_signal = 1;
	ft_putchar_fd('\n', STDIN_FILENO);
	//rl_replace_line("", 0);
	//rl_on_new_line();
	//rl_redisplay();
}

//• In interactive mode:
//	◦ ctrl-C displays a new prompt on a new line.
//	◦ ctrl-D exits the shell.
//	◦ ctrl-\ does nothing.

//non interactive mode:
//	ctrl-C exits whatever your running 

void	set_signals_inter(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, interactive_handler);
	//printf("signals interactive\n");
}

void	set_signals_non_inter(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, non_inter_handler);
	//printf("signals now non-interactive\n");
}
