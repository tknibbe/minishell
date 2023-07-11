/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cris_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:53:44 by cvan-sch          #+#    #+#             */
/*   Updated: 2023/07/11 18:11:21 by tknibbe          ###   ########.fr       */
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
	if (!all->data)
		ft_exit("Malloc error\n", errno);
	all->env = env_init(envp);
	all->data = malloc(sizeof(t_data));
	all->data->list = NULL;
	return (all);
}

void	tymon(t_ally *all, char *input)
{
	if (set_tokens(input, &all->data))
		return ;
	parse(input, &all->data);
}

void	cris(t_ally *all, char *input)
{
	printf("eroor, doe beter code ofzo\n");
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*string;
	char	*prompt;
	t_ally	*all;

	// I changed it here so that the executables name will be the prompt :)
	if (argc != 1)
		ft_exit("just ./minishell is enough\n", 1);
	all = minishell_init(envp);
	prompt = ft_strjoin(&argv[0][2], " -> ");
	if (!prompt)
		ft_exit("Error: malloc failure\n", errno);
	while (1)
	{
		string = readline(prompt);
		if (!string)
			ft_exit("wtf!\n", 2000000);
		if (ft_strncmp(string, "exit", 4) == 0)
			exit(0);
		 tymon(all, string);
		//cris(all, string); //graag hier onze tests in uitvoeren zodat we maar 1 ding hoeven te commenten
		history(string);
		free(string);
	}
	free(prompt);
}
