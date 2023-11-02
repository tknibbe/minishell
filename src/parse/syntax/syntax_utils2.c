/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 15:14:24 by tknibbe           #+#    #+#             */
/*   Updated: 2023/11/02 14:03:03 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

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

void	unclosed_warning(char c)
{
	write(STDERR_FILENO, "WARNING: unclosed `", 20);
	write(STDERR_FILENO, &c, 1);
	write(STDERR_FILENO, "` was ignored\n", 15);
}
