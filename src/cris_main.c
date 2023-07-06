/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cris_main.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tknibbe <tknibbe@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/14 14:53:44 by cvan-sch      #+#    #+#                 */
/*   Updated: 2023/07/06 18:33:11 by cvan-sch      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <env.h>
#include <built_ins.h>

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
	char	*prompt;
	t_ally	*all;

	// I changed it here so that the executables name will be the prompt :)
	if (argc != 1)
		ft_exit("just minishell is enough\n", 1);
	all = minishell_init(envp);
	prompt = ft_strjoin(&argv[0][2], " -> ");
	if (!prompt)
		ft_exit("Error: malloc failure\n", errno);
	while (1)
	{
		string = readline(prompt);
		if (!string)
			ft_exit("wtf!\n", 2000000);
		//parse_and_execute(string);
		//set_tokens(string, data);
		history(string);
		free(string);
	}
	free(prompt);
}
