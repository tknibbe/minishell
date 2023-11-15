/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   super_duper_awesome_tymon_and_cris_main.c          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 12:32:28 by tknibbe           #+#    #+#             */
/*   Updated: 2023/11/15 12:32:29 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run_single_command(t_list *list, t_env_info *e)
{
	char	*string;

	string = get_next_line(STDIN_FILENO);
	if (string && *string)
	{
		add_history(string);
		list = parse_input(string, e);
		if (list)
			executor(list, e);
		free(string);
	}
	return (e->last_exit_status);
}

int	run_shell(t_list *list, t_env_info *e)
{
	char	*string;

	while (1)
	{
		set_signals_inter();
		string = readline(PROMPT);
		set_signals_non_inter();
		if (!string)
			exit(0);
		if (*string)
		{
			add_history(string);
			list = parse_input(string, e);
			if (list)
				executor(list, e);
		}
		free(string);
	}
	exit (e->last_exit_status);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_env_info	*e;

	if (argc != 1)
		ft_minishell_error(argv[1], "...", "too many arguments", 1);
	e = env_init(envp);
	if (!isatty(STDIN_FILENO))
		exit(run_single_command(NULL, e));
	return (run_shell(NULL, e));
}
