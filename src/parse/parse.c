/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 14:26:34 by tknibbe           #+#    #+#             */
/*   Updated: 2023/07/13 14:37:41 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	parse_input(char *input, t_ally *all)
{
	if (set_tokens(input, &all->data))
		return ;
	parse(input, &all->data);
	//print_test(*data, input);
	//print_tokens(*data, input);
	//print_whole_list(all->data, input);
}
