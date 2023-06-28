/* ************************************************************************** */
/*                                                                            */
<<<<<<< HEAD
/*                                                        ::::::::            */
/*   cris_main.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tknibbe <tknibbe@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/14 14:53:44 by cvan-sch      #+#    #+#                 */
/*   Updated: 2023/06/28 13:50:51 by cvan-sch      ########   odam.nl         */
=======
/*                                                        :::      ::::::::   */
/*   cris_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:53:44 by cvan-sch          #+#    #+#             */
/*   Updated: 2023/06/28 15:25:36 by tknibbe          ###   ########.fr       */
>>>>>>> main
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	main(int argc, char *argv[], char *envp[])
{
	char	*string;
	t_data	*data = malloc(sizeof(t_data));

	t_env	*env = env_init(envp);
	while (1)
	{
<<<<<<< HEAD
		string = readline("minshell>\n");
=======
		string = readline("test/>");
		//history_management(string);
>>>>>>> main
		//parse_and_execute(string);
		set_tokens(string, data);
		if (strcmp(string, "exit") == 0)
			exit (0);
		free(string);
	}
}
