/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cris_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:53:44 by cvan-sch          #+#    #+#             */
/*   Updated: 2023/06/29 16:12:53 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <token.h>

int	main(void)
{
	char	*string;
	t_data	*data = malloc(sizeof(t_data));

	while (1)
	{
		string = readline("test/>");
		//history_management(string);
		//parse_and_execute(string);
		set_tokens(string, data);
		if (strcmp(string, "exit") == 0)
		{
			clear_history();
			exit (0);
		}
		//printf("%s\n", string);
		free(string);
	}
}
