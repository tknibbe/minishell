/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tknibbe <tknibbe@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/01 17:24:49 by tknibbe       #+#    #+#                 */
/*   Updated: 2023/06/28 12:34:11 by cvan-sch      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

//#include "../includes/minishell.h"

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int	main(int argc, char **argv)
{
	printf("minishell/>");
	readline(NULL);

	return (0);
}
