/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cris_main.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tknibbe <tknibbe@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/14 14:53:44 by cvan-sch      #+#    #+#                 */
/*   Updated: 2023/06/14 19:28:26 by cvan-sch      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	main(void)
{
	char	*string;
	char	buff[256];

	while (1)
	{
		string = readline("cris en tymon hun superduper coole minishell> ");
		history_management(string);
		printf("chdir: %s\n", getcwd(buff, 256));
		change_directory("..");
		printf("chdir: %s\n", getcwd(buff, 256));
		//parse_and_execute(string);
		if (strcmp(string, "exit") == 0)
		{
			clear_history();
			exit (0);
		}
		printf("%s\n", string);
		free(string);
	}
}
