/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cris_main.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tknibbe <tknibbe@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/14 14:53:44 by cvan-sch      #+#    #+#                 */
/*   Updated: 2023/07/02 11:33:20 by cvan-sch      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <env.h>

int	main(int argc, char *argv[], char *envp[])
{
	char	*string;
	t_data	*data = malloc(sizeof(t_data));

	//print_double_array(envp);
	t_env	*ev = env_init(envp);
	char	**tmp;
	while (1)
	{
		string = readline("minshell>");
		if (!string)
			printf("jaja");
		if (!ft_strncmp(string, "env", 4))
			env(ev->env);
		else if (!ft_strncmp(string, "unset ", 5))
		{
			tmp = ft_split(&string[6], ' ');
			unset(ev, tmp);
		}
		else if (!ft_strncmp(string, "export ", 6))
		{
			tmp = ft_split(&string[7], ' ');
			//printf("get's in to the unset function with : %s\n", &string[7]);
			export(ev, tmp);
		}
		else if (strcmp(string, "exit") == 0)
			exit (0);
		//parse_and_execute(string);
		//set_tokens(string, data);
		free(string);
	}
}
