/* ************************************************************************** */
/*                                                                            */
<<<<<<< HEAD:src/main.c
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tknibbe <tknibbe@student.42.fr>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/01 17:24:49 by tknibbe       #+#    #+#                 */
/*   Updated: 2023/06/28 12:34:11 by cvan-sch      ########   odam.nl         */
=======
/*                                                        :::      ::::::::   */
/*   exit_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 12:33:22 by tknibbe           #+#    #+#             */
/*   Updated: 2023/06/28 12:35:12 by tknibbe          ###   ########.fr       */
>>>>>>> main:src/exit_funcs.c
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_exit(char *string, int errnum)
{
<<<<<<< HEAD:src/main.c
	printf("minishell/>");
	readline(NULL);

	return (0);
=======
	write(2, string, ft_strlen(string));
	exit(errnum);
>>>>>>> main:src/exit_funcs.c
}
