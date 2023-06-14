/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 11:10:47 by tknibbe           #+#    #+#             */
/*   Updated: 2023/02/03 15:25:14 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

char	*free_and_join(char *buffer, char *read_line)
{
	char	*new_buffer;

	new_buffer = ft_strjoin(buffer, read_line);
	free (buffer);
	free (read_line);
	if (new_buffer == NULL)
		return (NULL);
	return (new_buffer);
}
