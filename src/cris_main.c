/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cris_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:53:44 by cvan-sch          #+#    #+#             */
/*   Updated: 2023/07/03 15:50:47 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <token.h>

void	print_struct(t_exec *list)
{
	while (list)
	{
		printf("instr = [%s] option = %d\n", list->instr, list->option);
		list = list->next;
	}
}

int	main(void)
{
	char	*string;
	t_data	*data = malloc(sizeof(t_data));

	while (1)
	{
		string = readline("minicris/>");
		history_management(string);
		//parse_and_execute(string);
		set_tokens(string, &data);
		make_list(&data, string);
		print_struct(data->list);
		if (strcmp(string, "exit") == 0)
		{
			clear_history();
			exit (0);
		}
		//printf("%s\n", string);
		free(string);
	}
}
