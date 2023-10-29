/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactive.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tymonknibbe <tymonknibbe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 15:35:50 by tknibbe           #+#    #+#             */
/*   Updated: 2023/10/29 21:42:22 by tymonknibbe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	interactive_handler(int c)
{
	(void)c;
	ft_putchar_fd('\n', STDIN_FILENO);
	// rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

/*The unset_echo function is used to modify the terminal settings to disable the
ECHOCTL flag. This flag, when disabled, causes the terminal to hide control
characters. The function retrieves the current terminal attributes using
tcgetattr disables ECHOCTL in the c_lflag field, and then sets the modified
attributes using tcsetattr.
If any error occurs during these operations, the function exits with an error 
message and the associated error code.*/
void	unset_echo(void)
{
	struct termios	term;

	if (tcgetattr(STDIN_FILENO, &term) != 0)
		ft_minishell_error("tcgetattr()", NULL, strerror(errno), errno);
	term.c_lflag &= ~ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) != 0)
		ft_minishell_error("tcgetattr()", NULL, strerror(errno), errno);
}

void	set_signals_inter(void)
{
	unset_echo();
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, interactive_handler);
}
