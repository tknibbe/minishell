/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactive.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 15:35:50 by tknibbe           #+#    #+#             */
/*   Updated: 2023/08/17 14:12:30 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	interactive_handler(int c)
{
	ft_putchar_fd('\n', STDIN_FILENO);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	unset_echo(void)
{
	struct termios	term;

	if (tcgetattr(STDIN_FILENO, &term) != 0)
		ft_exit("Error getting terminal attributes", errno);
	term.c_lflag &= ~ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) != 0)
		ft_exit("Error setting terminal attributes", errno);
}

void	set_signals_inter(void)
{
	unset_echo();
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, interactive_handler);
}
