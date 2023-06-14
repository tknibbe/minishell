/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cris_main.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: cvan-sch <cvan-sch@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/14 14:53:44 by cvan-sch      #+#    #+#                 */
/*   Updated: 2023/06/14 14:55:18 by cvan-sch      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <readline/history.h>
#include <readline/readline.h>

int	main(void)
{
	char *string = readline("minishell/>");
	printf("string: %s\n", string);
}