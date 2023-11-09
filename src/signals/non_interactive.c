/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   non_interactive.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 13:41:26 by tknibbe           #+#    #+#             */
/*   Updated: 2023/11/09 15:10:53 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
	interactive mode:

	ECHOCTL in termios (cl(set/get)attr) needs to be turned off
		ctrl-C displays a new prompt on a new line.
		ctrl-D exits the shell.
		ctrl-\ does nothing.
*/

/*
	non interactive mode:

		ctrl-C exits whatever your running 
		ctrl-\ is ignored
		ctrl-D sends EOF -- is working automatically
*/

void	non_inter_handler(int c)
{
	(void)c;
	ft_putchar_fd('\n', STDIN_FILENO);
}

/*
	The set_echo function is used to modify the terminal settings to include the
	ECHOCTL flag. This flag, when enabled, causes the terminal to echo control
	characters as-is. It first retrieves the current terminal attributes using
	tcgetattr, enables ECHOCTL in the c_lflag field, and then sets the modified
	attributes using tcsetattr.
	If any error occurs during these operations, the function exits with an error
	message and the associated error code.
*/
static void	set_echo(void)
{
	struct termios	term;

	if (tcgetattr(STDIN_FILENO, &term) != 0)
		ft_minishell_error("tcgetattr()", NULL, strerror(errno), errno);
	term.c_lflag |= ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) != 0)
		ft_minishell_error("tcgetattr()", NULL, strerror(errno), errno);
}

void	set_signals_non_inter(void)
{
	set_echo();
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, non_inter_handler);
}
