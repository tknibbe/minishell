/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cris_main.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tknibbe <tknibbe@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/14 14:53:44 by cvan-sch      #+#    #+#                 */
/*   Updated: 2023/06/28 13:50:51 by cvan-sch      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	main(int argc, char *argv[], char *envp[])
{
	char	*string;
	char	buff[256];

	t_env	*env = env_init(envp);
	while (1)
	{
		string = readline("minshell>\n");
		//parse_and_execute(string);
		if (strcmp(string, "exit") == 0)
			exit (0);
		free(string);
	}
}
