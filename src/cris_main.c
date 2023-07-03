/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cris_main.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tknibbe <tknibbe@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/14 14:53:44 by cvan-sch      #+#    #+#                 */
/*   Updated: 2023/07/03 15:47:43 by cvan-sch      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <env.h>

t_ally	*minishell_init(char *envp[])
{
	t_ally	*all;

/*	create everything that needs to be initialized here and store it in all	*/

	all = malloc(sizeof(t_ally));
	if (!all)
		ft_exit("Error: allocation failed\n", errno);
	all->env = env_init(envp);
	return (all);
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*string;
	t_ally	*all;

	all = minishell_init(envp);
	while (1)
	{
		string = readline("minicris/>");
		if (!string)
			printf("jaja");
		//parse_and_execute(string);
		//set_tokens(string, data);
		free(string);
	}
}
