/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cris_main.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tknibbe <tknibbe@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/14 14:53:44 by cvan-sch      #+#    #+#                 */
/*   Updated: 2023/06/28 17:56:18 by cvan-sch      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	main(int argc, char *argv[], char *envp[])
{
	char	*string;
	t_data	*data = malloc(sizeof(t_data));

	print_double_array(envp);
	char *to_unset[] = {"TERM", "TERM_PROGRAM", "TMPDIR", "SHELL", NULL};
	t_env	*env = env_init(envp);
	unset(env, to_unset);
	while (1)
	{
		string = readline("minshell>");
		//parse_and_execute(string);
		//set_tokens(string, data);
		if (strcmp(string, "exit") == 0)
			exit (0);
		free(string);
	}
}
