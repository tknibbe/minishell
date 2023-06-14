/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 11:14:06 by tknibbe           #+#    #+#             */
/*   Updated: 2023/02/08 17:01:01 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <limits.h>
# include <stdlib.h>
# include "libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

//get_next_line.c
char	*get_next_line(int fd);
char	*get_buffer(int fd, char *buffer);
char	*filter_line(char *buffer);
char	*get_new_buffer(char *buffer);
//get_next_line_utils
char	*free_and_join(char *buffer, char *read_line);
#endif
