/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 10:58:42 by tknibbe           #+#    #+#             */
/*   Updated: 2023/02/03 15:24:45 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

//ft_printf.c
int		ft_printf(const char *input_string, ...);
int		check_flags(va_list args, char *input_string, int i);
int		middle_man(va_list args, char *input_string, int count);
//c_s_u_d_i_conversion.c
int		c_conversion(int s);
int		s_conversion(char *s);
int		d_conversion(int s);
int		i_conversion(int s);
int		u_conversion(unsigned int s);
//hex_conversion.c
int		p_conversion(unsigned long s);
int		lower_x_conversion(unsigned int s);
int		upper_x_conversion(unsigned int s);
int		hex_conversion(unsigned long s, char *hex, int count);
// more_functions
int		out_unsigned_nbr(int count, unsigned int n);
int		out_nbr(int count, int n);
int		ft_strlen(const char *s);
int		write_substr(char const *s, unsigned int start, size_t len);

#endif