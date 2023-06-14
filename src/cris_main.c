/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cris_main.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tknibbe <tknibbe@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/14 14:53:44 by cvan-sch      #+#    #+#                 */
/*   Updated: 2023/06/14 16:36:59 by cvan-sch      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	main(void)
{
	char	*string;

	while (1)
	{
		string = readline("minishell/>");
		history_management(string);
		//parse_and_execute(string);
		if (strcmp(string, "exit") == 0)
			exit (0);
		printf("%s\n", string);
		free(string);
	}
}
