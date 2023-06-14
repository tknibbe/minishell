/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cris_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:53:44 by cvan-sch          #+#    #+#             */
/*   Updated: 2023/06/14 16:11:48 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <string.h>

int	main(void)
{
	char	*string;

	while (1)
	{
		string = readline("minishell/>");
		//parse_and_execute(string);
		
		if (strcmp(string, "exit") == 0)
			return (0);
		printf("%s\n", string);
	}
}
