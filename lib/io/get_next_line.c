/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 11:09:58 by tknibbe           #+#    #+#             */
/*   Updated: 2023/02/03 15:25:08 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*buffer[1024];
	char		*return_line;

	if (fd < 0 || BUFFER_SIZE < 0 || BUFFER_SIZE > 2147483646)
		return (NULL);
	if (!buffer[fd])
		buffer[fd] = ft_calloc(1, 1);
	if (!buffer[fd])
		return (NULL);
	buffer[fd] = (get_buffer(fd, buffer[fd]));
	if (!buffer[fd])
		return (NULL);
	return_line = filter_line(buffer[fd]);
	if (!return_line)
	{
		free (buffer[fd]);
		buffer[fd] = NULL;
		return (NULL);
	}
	buffer[fd] = get_new_buffer(buffer[fd]);
	if (!buffer[fd])
		free(buffer[fd]);
	return (return_line);
}

char	*get_buffer(int fd, char *buffer)
{
	char	*read_line;
	int		read_check;

	read_check = 1;
	while (!ft_strchr(buffer, '\n') && read_check > 0)
	{
		read_line = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
		if (!read_line)
			return (free (buffer), NULL);
		read_check = read(fd, read_line, BUFFER_SIZE);
		if (read_check < 0)
			return (free (buffer), free (read_line), NULL);
		buffer = free_and_join(buffer, read_line);
		if (!buffer)
			return (NULL);
	}
	return (buffer);
}

char	*filter_line(char *buffer)
{
	int		i;
	char	*line;

	i = 0;
	if (buffer[i] == '\0')
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	line = ft_calloc (i + 1, sizeof(char));
	if (line == 0)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	line[i] = buffer[i];
	return (line);
}

char	*get_new_buffer(char *buffer)
{
	char	*new_buffer;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
		return (free (buffer), NULL);
	new_buffer = ft_calloc(ft_strlen(buffer) - i + 1, sizeof(char));
	if (new_buffer == 0)
		return (free(buffer), NULL);
	i++;
	while (buffer[i])
	{
		new_buffer[j] = buffer[i];
		j++;
		i++;
	}
	free (buffer);
	return (new_buffer);
}
