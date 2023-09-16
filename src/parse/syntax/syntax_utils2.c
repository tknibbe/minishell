/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 15:14:24 by tknibbe           #+#    #+#             */
/*   Updated: 2023/09/09 15:14:54 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parsing.h>

int	is_redirect(int t)
{
	return (t == REDIRLEFT || t == REDIRRIGHT || t == HEREDOC || t == APPEND);
}

int	is_control_op(int token)
{
	return (token == OR || token == AND || token == PIPESYMBOL);
}
