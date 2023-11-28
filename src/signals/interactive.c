/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactive.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 15:35:50 by tknibbe           #+#    #+#             */
/*   Updated: 2023/11/28 17:49:49 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*returns a value based on if there has been a signal interruption
0 on no interruption
the exit code if there has been an interruption*/
int	pretty_much_a_global(int mode, int value)
{
	static int	not_a_global;

	if (mode == SET)
	{
		not_a_global = value;
		return (EXIT_SUCCESS);
	}
	if (mode == GET)
	{
		value = not_a_global;
		not_a_global = 0;
	}
	if (mode == CHECK)
		value = not_a_global;
	return (value);
}

static void	interactive_handler(int c)
{
	(void)c;
	ft_putchar_fd('\n', STDIN_FILENO);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	pretty_much_a_global(SET, 130);
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

	if (isatty(STDIN_FILENO))
	{
		if (tcgetattr(STDIN_FILENO, &term) != 0)
			ft_minishell_error("tcgetattr()", NULL, strerror(errno), errno);
		term.c_lflag &= ~ECHOCTL;
		if (tcsetattr(STDIN_FILENO, TCSANOW, &term) != 0)
			ft_minishell_error("tcgetattr()", NULL, strerror(errno), errno);
	}
}

void	set_signals_inter(void)
{
	unset_echo();
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, interactive_handler);
}
