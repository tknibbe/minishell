/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tymonknibbe <tymonknibbe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 15:14:24 by tknibbe           #+#    #+#             */
/*   Updated: 2023/10/27 16:31:06 by tymonknibbe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parsing.h>

int	is_redirect(int t)
{
	return (t == REDIRLEFT || t == REDIRRIGHT || t == HEREDOC_EXP || t == APPEND);
}

int	is_control_op(int token)
{
	return (token == OR || token == AND || token == PIPESYMBOL);
}

int	no_valid_token(t_list *list)
{
	int	i;

	i = 0;
	while (list->input[i])
	{
		if (list->token[i] != BLANK)
			return (EXIT_SUCCESS);
		i++;
	}
	return (EXIT_FAILURE);
}
